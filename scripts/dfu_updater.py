import sys
import serial
import time

from elftools.elf.elffile import ELFFile

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
    """Documentation for dfu_updater class.

    More details.
    """

    def __init__(self):
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
        if isinstance(self.usart, serial.Serial):
            print("The usart is already initialized...")
        else:
            print("Initializing...")
            self.usart = serial.Serial(port = self.port, baudrate = self.baudrate, timeout = 120.0)
            if isinstance(self.usart, serial.Serial):
                print("Initialization completed!")
            else:
                print("Initialization can not be completed..")

    def deinit(self):
        if isinstance(self.usart, serial.Serial):
            print("Deinitialization...")
            self.usart.close()
            self.usart = None
            if isinstance(self.usart, serial.Serial):
                print("Deinitialization can not be completed..")
            else:
                print("Deinitialization completed!")

    def transmit(self):
        for byte in self.instance.serialized.buffer:
            self.usart.write(byte.to_bytes(1, byteorder = 'big'))

    def receive(self):
        serialized_packet_size = DUST_PACKET_HEADER_SIZE + self.instance.options.payload_size + DUST_PACKET_CRC16_SIZE
        serialized_packet = self.usart.read(size=serialized_packet_size)
        if (self.instance.packet.deserialize(serialized_packet) != DUST_RESULT.SUCCESS.value):
            return DUST_RESULT.ERROR.value
        return DUST_RESULT.SUCCESS.value

    def connect(self, ack_frequency, payload_size):
        if isinstance(self.usart, serial.Serial):
            print("Trying to connect...")
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
        if isinstance(self.usart, serial.Serial):
            print("Waiting for disconnection...")
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
        if isinstance(self.usart, serial.Serial):
            print("Trying to update...")
            packet_number = 0
            payload_size = self.length_hash_table[self.instance.options.payload_size]
            while packet_number < self.instance.options.number_of_packets:
                self.instance.packet.header.create(DUST_OPCODE.DATA.value, payload_size, DUST_ACK.UNSET.value, packet_number)
                self.instance.packet.payload.create(buffer=self.fill_data(packet_number))
                self.instance.packet.create(self.instance.packet.header, self.instance.packet.payload)
                self.instance.serialized.create(buffer=self.instance.packet.serialize())
                self.transmit()
                if ((((packet_number + 1)  % self.ack_frequency_hash_table[self.instance.options.ack_frequency]) == 0) or
                     ((packet_number + 1) == self.instance.options.number_of_packets)):
                    if (self.receive() == DUST_RESULT.SUCCESS.value):
                        if (self.instance.packet.header.bits.ack == DUST_ACK.SET.value):
                            print("#" + str(packet_number) + ": ACK")
                        else:
                            print("#" + str(packet_number) + ": NACK")
                            packet_number -= self.ack_frequency_hash_table[self.instance.options.ack_frequency]
                packet_number += 1
        else:
            print("Usart is not initialized...")

    def readelf_get_sections(self, segment):
        with open(self.bin, 'rb') as bin_file:
            self.elf = ELFFile(bin_file)
            for section in self.elf.iter_sections():
                if (section.name.startswith(segment.name)):
                    segment.sections.append(section)
            segment.fill_raw_hexdata()

    def calculate_number_of_packets(self, firmware_size, payload_size):
        if ((firmware_size % payload_size) != 0):
            return int((firmware_size / payload_size) + 1)
        else:
            return int(firmware_size / payload_size)

    def prepare_data(self):
        number_of_alignment_bytes = (self.instance.options.payload_size - (len(self.text.converted_hexdata) % self.instance.options.payload_size))
        for i in range(0, number_of_alignment_bytes):
            self.text.converted_hexdata.append(0xff)

    def fill_data(self, packet_number):
        payload_size = self.instance.options.payload_size
        return self.text.converted_hexdata[(packet_number * payload_size):((packet_number * payload_size) + payload_size)]

    def print_arguments(self):
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
