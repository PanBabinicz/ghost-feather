import sys
import serial
import time

from elftools.elf.elffile import ELFFile
from tqdm import tqdm

from dust_packet import dust_crc16_generate_lut
from dust_packet import dust_packet
from dust_packet import dust_header
from dust_packet import dust_handshake_options
from dust_packet import dust_instance
from dust_packet import DUST_RESULT
from dust_packet import DUST_OPCODE
from dust_packet import DUST_LENGTH
from dust_packet import DUST_ACK
from dust_packet import DUST_ACK_FREQUENCY
from dust_packet import DUST_PACKET_HEADER_SIZE
from dust_packet import DUST_PACKET_CRC16_SIZE

from dfu_updater_segment import dfu_updater_segment

class dfu_updater:
    """
    @class dfu_updater
    @brief Handles the DFU (Device Firmware Update) process over USART.

    This class provides functionality to manage the firmware update process, including
    setting up USART communication, initializing required components, and maintaining
    hash tables for length and acknowledgment frequency configurations.
    """

    def __init__(self):
        """
        @brief Constructor for the dfu_updater class.

        Initializes the DFU updater by parsing command-line arguments, setting up
        essential attributes such as the binary file path, port, and baud rate, and
        preparing default configurations for the dust protocol.

        @note The script expects the following arguments in order:
              <bin> <port> <baudrate>.

        Example: python3 dfu_usart.py firmware.bin COM3 9600
        """
        if ( len(sys.argv) < 4 ):
            print("Invalid usage: python3 dfu_usart.py <bin> <port> <baudrate>")
            sys.exit()
        self.bin               = sys.argv[1]
        self.port              = sys.argv[2]
        self.baudrate          = sys.argv[3]
        self.text              = dfu_updater_segment(name = '.text', sections = [])
        self.usart             = None
        self.instance          = dust_instance()
        self.length_hash_table = {
            0x20  : DUST_LENGTH.BYTES32.value,
            0x40  : DUST_LENGTH.BYTES64.value,
            0x80  : DUST_LENGTH.BYTES128.value,
            0x100 : DUST_LENGTH.BYTES256.value
        }
        self.ack_frequency_hash_table = {
            DUST_ACK_FREQUENCY.AFTER_EACH_PACKET.value : 0x01,
            DUST_ACK_FREQUENCY.AFTER_8_PACKETS.value   : 0x08,
            DUST_ACK_FREQUENCY.AFTER_16_PACKETS.value  : 0x10,
            DUST_ACK_FREQUENCY.AFTER_32_PACKETS.value  : 0x20,
            DUST_ACK_FREQUENCY.AFTER_64_PACKETS.value  : 0x40,
            DUST_ACK_FREQUENCY.AFTER_128_PACKETS.value : 0x80,
            DUST_ACK_FREQUENCY.AFTER_256_PACKETS.value : 0x100,
            DUST_ACK_FREQUENCY.AFTER_512_PACKETS.value : 0x200
        }

    def init(self):
        """
        @brief Initializes the USART connection.

        This method sets up a serial connection using the specified port and baud rate.
        It checks whether the USART is already initialized and prints status messages
        accordingly.

        @note Timeout for the USART connection is set to 120 seconds.
        """
        if isinstance(self.usart, serial.Serial):
            print("The usart is already initialized...")
        else:
            print("\nInitializing...")
            self.usart = serial.Serial(port = self.port, baudrate = self.baudrate, timeout = 120.0)
            if isinstance(self.usart, serial.Serial):
                print("Initialization completed!")
            else:
                print("Initialization can not be completed..")

    def deinit(self):
        """
        @brief Deinitializes the USART connection.

        This method closes the serial connection and releases the USART resource.
        It prints status messages indicating whether the deinitialization was successful.
        """
        if isinstance(self.usart, serial.Serial):
            print("\nDeinitialization...")
            self.usart.close()
            self.usart = None
            if isinstance(self.usart, serial.Serial):
                print("Deinitialization can not be completed..")
            else:
                print("Deinitialization completed!")

    def transmit(self):
        """
        @brief Transmits serialized data over USART.

        This method writes each byte from the serialized buffer of the dust instance
        to the USART interface.

        @note Ensure that the USART connection is initialized before calling this method.
        """
        for byte in self.instance.serialized.buffer:
            self.usart.write(byte.to_bytes(1, byteorder = 'big'))

    def receive(self):
        """
        @brief Receives a serialized packet from USART.

        This method reads a packet of a specific size from the USART interface, deserializes
        the received data, and validates its integrity.

        @return DUST_RESULT.SUCCESS.value On successful deserialization and validation.
        @return DUST_RESULT.ERROR.value   If the packet is corrupted or deserialization fails.
        """
        serialized_packet_size = DUST_PACKET_HEADER_SIZE + self.instance.options.payload_size + DUST_PACKET_CRC16_SIZE
        serialized_packet = self.usart.read(size=serialized_packet_size)
        if (self.instance.packet.deserialize(serialized_packet) != DUST_RESULT.SUCCESS.value):
            return DUST_RESULT.ERROR.value
        return DUST_RESULT.SUCCESS.value

    def connect(self, ack_frequency, payload_size):
        """
        @brief Establishes a connection using the dust protocol.

        This method prepares and sends a connect packet to the device using the USART interface.
        It configures the dust instance options, creates the connection packet, transmits it,
        and validates the acknowledgment response.

        @param ack_frequency The acknowledgment frequency to be used during communication.
        @param payload_size  The size of the payload for each packet.

        @note Ensure that the USART connection is initialized before calling this method.
        """
        if isinstance(self.usart, serial.Serial):
            print("\nTrying to connect...")
            number_of_packets = self.calculate_number_of_packets(self.text.size, payload_size)
            self.instance.options.create(ack_frequency, number_of_packets, payload_size)
            self.instance.packet.header.create(DUST_OPCODE.CONNECT.value, DUST_LENGTH.BYTES32.value, DUST_ACK.UNSET.value, packet_number=0x00)
            self.instance.packet.payload.create(buffer=self.instance.options.serialize())
            self.instance.packet.create(self.instance.packet.header, self.instance.packet.payload)
            self.instance.serialized.create(buffer=self.instance.packet.serialize())
            self.transmit()
            if (self.receive() == DUST_RESULT.SUCCESS.value):
                if (self.instance.packet.header.bits.ack == DUST_ACK.SET.value):
                    print("Connected")
                else:
                    print("ACK was not received")
        else:
            print("Usart is not initialized...")

    def disconnect(self):
        """
        @brief Disconnects from the device using the Dust protocol.

        This method waits for a disconnection packet from the device, validates it,
        and sends a disconnection acknowledgment (ACK) packet back. The method ensures
        proper handshake and acknowledgment before completing the disconnection.

        @return DUST_RESULT.SUCCESS.value On successful disconnection.
        @return DUST_RESULT.ERROR.value   If the disconnection fails or an error occurs.
        """
        if isinstance(self.usart, serial.Serial):
            print("\nWaiting for disconnection...")
            if (self.receive() != DUST_RESULT.SUCCESS.value):
                print("Corrupted packet was received during disconnection process")
                return DUST_RESULT.ERROR.value
            if (self.instance.packet.header.bits.opcode == DUST_OPCODE.DISCONNECT.value):
                print("Send the disconnection ACK packet")
                self.instance.packet.header.create(DUST_OPCODE.DISCONNECT.value, DUST_LENGTH.BYTES32.value, DUST_ACK.SET.value, packet_number=0x01)
                self.instance.packet.payload.create(buffer=[0x00]*self.instance.options.payload_size)
                self.instance.packet.create(self.instance.packet.header, self.instance.packet.payload)
                self.instance.serialized.create(buffer=self.instance.packet.serialize())
                while True:
                    self.transmit()
                    if (self.receive() == DUST_RESULT.SUCCESS.value):
                        if (self.instance.packet.header.bits.ack == DUST_ACK.SET.value):
                            print("Disconnection received ACK")
                            break
                        else:
                            print("Disconnection received NACK")
                    else:
                        print("Receive result ERROR")
                return DUST_RESULT.SUCCESS.value
        else:
            print("Usart is not initialized...")
            return DUST_RESULT.ERROR.value

    def update(self):
        """
        @brief Updates the device firmware using the dust protocol.

        This method sends firmware data to the device in packets. Each packet is prepared
        with appropriate headers, payloads, and serialization. ACKs are received periodically
        based on the specified acknowledgment frequency.

        @note Ensure that the USART connection is initialized before calling this method.
        """
        # TODO: Check the retransmission machanism
        if isinstance(self.usart, serial.Serial):
            print("\nTrying to update...")
            packet_number = 0
            payload_size = self.length_hash_table[self.instance.options.payload_size]
            for packet_number in tqdm(range(self.instance.options.number_of_packets)):
                self.instance.packet.header.create(DUST_OPCODE.DATA.value, payload_size, DUST_ACK.UNSET.value, packet_number)
                self.instance.packet.payload.create(buffer=self.fill_data(packet_number))
                self.instance.packet.create(self.instance.packet.header, self.instance.packet.payload)
                self.instance.serialized.create(buffer=self.instance.packet.serialize())
                self.transmit()
                if ((((packet_number + 1)  % self.ack_frequency_hash_table[self.instance.options.ack_frequency]) == 0) or
                     ((packet_number + 1) == self.instance.options.number_of_packets)):
                    if (self.receive() == DUST_RESULT.SUCCESS.value):
                        if (self.instance.packet.header.bits.ack != DUST_ACK.SET.value):
                            packet_number -= self.ack_frequency_hash_table[self.instance.options.ack_frequency]
        else:
            print("Usart is not initialized...")

    def readelf_get_sections(self, segment):
        """
        @brief Reads ELF sections that match the given segment name.

        This method iterates through the sections of the ELF binary and appends sections
        matching the segment name to the segment. The raw hex data of the segment is also populated.

        @param segment The dfu_updater_segment instance to populate with sections and raw hex data.
        """
        with open(self.bin, 'rb') as bin_file:
            self.elf = ELFFile(bin_file)
            for section in self.elf.iter_sections():
                if (section.name.startswith(segment.name)):
                    segment.sections.append(section)
            segment.fill_raw_hexdata()

    def calculate_number_of_packets(self, firmware_size, payload_size):
        """
        @brief Calculates the number of packets required for firmware transmission.

        This method determines the number of packets needed to send the firmware based on
        its size and the payload size.

        @param firmware_size The size of the firmware in bytes.
        @param payload_size The size of the payload in bytes for each packet.

        @return The total number of packets required.
        """
        if ((firmware_size % payload_size) != 0):
            return int((firmware_size / payload_size) + 1)
        else:
            return int(firmware_size / payload_size)

    def prepare_data(self):
        """
        @brief Prepares firmware data by aligning it to the payload size.

        This method appends padding bytes (0xFF) to the firmware data to ensure its size
        aligns with the payload size defined in the dust instance options.

        @note This method should be called before transmitting firmware data.
        """
        number_of_alignment_bytes = (self.instance.options.payload_size - (len(self.text.converted_hexdata) % self.instance.options.payload_size))
        for i in range(0, number_of_alignment_bytes):
            self.text.converted_hexdata.append(0xff)

    def fill_data(self, packet_number):
        """
        @brief Fills the payload data for a specific packet.

        This method fills a slice of firmware data corresponding to the given packet number
        and payload size.

        @param packet_number The index of the packet to fill data for.

        @return A list containing the payload data for the specified packet.
        """
        payload_size = self.instance.options.payload_size
        return self.text.converted_hexdata[(packet_number * payload_size):((packet_number * payload_size) + payload_size)]

    def print_arguments(self):
        """
        @brief Prints the command-line arguments used to initialize the dfu_updater instance.

        This method displays the binary file path, serial port, and baud rate provided
        during initialization.
        """
        print("Bin:      " + self.bin)
        print("Port:     " + self.port)
        print("Baudrate: " + self.baudrate)


updater = dfu_updater()
updater.print_arguments()

updater.readelf_get_sections(updater.text)
updater.text.calculate_size()
updater.text.convert_to_little_endian()

dust_crc16_generate_lut(0x1021)

updater.init()
updater.connect(DUST_ACK_FREQUENCY.AFTER_EACH_PACKET.value, 32)
updater.prepare_data()
updater.update()
updater.disconnect()
updater.deinit()
