import sys
import serial
import time

from elftools.elf.elffile import ELFFile

from dust_packet import dust_packet
from dust_packet import dust_header
from dust_packet import dust_handshake_options
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
        self.bin      = sys.argv[1]
        self.port     = sys.argv[2]
        self.baudrate = sys.argv[3]
        self.text     = dfu_updater_segment(name = '.text', sections = [])
        self.packet   = dust_packet()
        self.options  = dust_handshake_options()
        self.usart    = None

    def print_arguments(self):
        print("Bin:      " + self.bin)
        print("Port:     " + self.port)
        print("Baudrate: " + self.baudrate)

    def readelf_get_sections(self, segment):
        with open(self.bin, 'rb') as bin_file:
            self.elf = ELFFile(bin_file)
            for section in self.elf.iter_sections():
                if (section.name.startswith(segment.name)):
                    segment.sections.append(section)
            segment.fill_raw_hexdata()

    def create_conntection_data(self):
        data = []
        data.append(self.options.ack_frequency)
        data.append((self.options.number_of_packets & 0xff000000) >> 0x18)
        data.append((self.options.number_of_packets & 0x00ff0000) >> 0x10)
        data.append((self.options.number_of_packets & 0x0000ff00) >> 0x08)
        data.append((self.options.number_of_packets & 0x000000ff) >> 0x00)
        data.append((self.options.payload_size & 0x0000ff00) >> 0x08)
        data.append((self.options.payload_size & 0x000000ff) >> 0x00)
        data.extend([0x00] * 25)
        return data

    def get_number_of_packets(self, firmware_size, payload_size):
        if ((firmware_size % payload_size) != 0):
            return int((firmware_size / payload_size) + 1)
        else:
            return int(firmware_size / payload_size)

    def fill_data(self, packet_number):
        return self.text.converted_hexdata[(packet_number * self.options.payload_size):((packet_number * self.options.payload_size) + self.options.payload_size)]

    def init(self):
        if isinstance(self.usart, serial.Serial):
            print("The usart is already initialized...")
        else:
            print("Initializing...")
            self.usart = serial.Serial(port = self.port, baudrate = self.baudrate, timeout = 60.0)
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

    def connect(self, ack_frequency, payload_size):
        if isinstance(self.usart, serial.Serial):
            print("Trying to connect...")
            self.options.ack_frequency = ack_frequency
            self.options.payload_size = self.packet.length_hash_table[payload_size]
            self.options.number_of_packets = self.get_number_of_packets(self.text.size, self.options.payload_size)
            self.packet.create(opcode = DUST_OPCODE.CONNECT.value, length = payload_size,
                               ack = DUST_ACK.UNSET.value, packet_number = 0x00, data = self.create_conntection_data())
            self.packet.serialize()
            self.transmit_packet()
            result = self.receive_ack()
            if result == DUST_RESULT.SUCCESS.value:
                print("Connected")
        else:
            print("Usart is not initialized...")

    def disconnect(self):
        if isinstance(self.usart, serial.Serial):
            print("Waiting for disconnection...")
            if (self.receive() != DUST_RESULT.SUCCESS.value):
                print("Corrupted packet was received during disconnection process")
                return DUST_RESULT.ERROR.value
            if (self.packet.header.bits.opcode == DUST_OPCODE.DISCONNECT.value):
                print("Send the disconnection ACK packet")
                self.packet.create(opcode = DUST_OPCODE.DISCONNECT.value,
                                   length = DUST_LENGTH.BYTES32.value,
                                   ack = DUST_ACK.SET.value,
                                   packet_number = 0x01,
                                   data = [0x00] * 32)
                self.packet.serialize()
                while True:
                    self.transmit_packet()
                    if (self.receive_ack() == DUST_RESULT.SUCCESS.value):
                        print("Disconnection receive ACK")
                        break
                    else:
                        print("Disconnection receive NACK")
        else:
            print("Usart is not initialized...")
            return DUST_RESULT.ERROR.value

    def update(self):
        if isinstance(self.usart, serial.Serial):
            print("Trying to update...")
            packet_number = 0
            flag = True
            while packet_number < self.options.number_of_packets:
                self.packet.create(opcode = DUST_OPCODE.DATA.value,
                                   length = DUST_LENGTH.BYTES32.value,
                                   ack = DUST_ACK.UNSET.value,
                                   packet_number = packet_number,
                                   data = self.fill_data(packet_number))
                self.packet.serialize()
                if flag and packet_number == 17:
                    self.packet.serialized[13] = 0xff
                    flag = False
                self.transmit_packet()
                if ((((packet_number + 1)  % self.packet.ack_frequency_hash_table[self.options.ack_frequency]) == 0) or
                     ((packet_number + 1) == self.options.number_of_packets)):
                    if (self.receive_ack() == DUST_RESULT.SUCCESS.value):
                        print("#" + str(packet_number) + ": ACK")
                    else:
                        print("#" + str(packet_number) + ": NACK")
                        packet_number -= self.packet.ack_frequency_hash_table[self.options.ack_frequency]
                packet_number += 1
        else:
            print("Usart is not initialized...")

    def transmit_packet(self):
        for byte in self.packet.serialized:
            self.usart.write(byte.to_bytes(1, byteorder = 'big'))

    def receive(self):
        serialized_packet_size = DUST_PACKET_HEADER_SIZE + self.options.payload_size + DUST_PACKET_CRC16_SIZE
        serialized_packet = self.usart.read(size = serialized_packet_size)
        if (self.packet.deserialize(serialized_packet) != DUST_RESULT.SUCCESS.value):
            return DUST_RESULT.ERROR.value
        return DUST_RESULT.SUCCESS.value

    def transmit_socat(self):
        byte_string = ""
        for byte in self.packet.serialized:
            byte_string += hex(byte)
            byte_string += " "
        for byte in byte_string:
            self.usart.write(byte.encode('utf-8'))
        self.usart.write(b"\n\r")

    def receive_ack(self):
        data = self.usart.read(size = DUST_PACKET_HEADER_SIZE)
        self.packet.header = self.packet.deserialize_header(data)
        if ((self.packet.header.bits.ack == DUST_ACK.SET.value) and
            (self.packet.header.bits.checksum == self.packet.calculate_checksum())):
            return DUST_RESULT.SUCCESS.value
        return DUST_RESULT.ERROR.value


updater = dfu_updater()
updater.print_arguments()

updater.readelf_get_sections(updater.text)
updater.text.calculate_size()
updater.text.convert_to_little_endian()
updater.packet.crc16_lookup_table_generate(0x1021)

updater.init()
updater.connect(ack_frequency = DUST_ACK_FREQUENCY.AFTER_EACH_PACKET.value, payload_size = DUST_LENGTH.BYTES32.value)
updater.update()
updater.disconnect()
updater.deinit()
