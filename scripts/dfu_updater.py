import sys
import serial

from elftools.elf.elffile import ELFFile

from dust_packet import dust_packet
from dust_packet import dust_header
from dust_packet import DUST_OPCODE
from dust_packet import DUST_LENGTH

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

    def connect(self):
        if isinstance(self.usart, serial.Serial):
            print("Trying to connect...")
            self.packet.create(opcode = 0x00, length = 0x00, packet_number = 0x00, data = [0xcc] * 32)
            self.packet.serialize()
            self.transmit_socat()
            #self.receive_socat()
        else:
            print("Usart is not initialized...")

    def disconnect(self):
        self.packet.create(opcode = 0x01, length = 0x00, packet_number = 0x00, data = [0xdd] * 32)
        self.packet.serialize()
        #self.transmit_socat()
        #self.receive_socat()

    def transmit_uc(self):
        for byte in self.packet.serialized:
            self.usart.write(byte)

    def transmit_socat(self):
        byte_string = ""
        for byte in self.packet.serialized:
            byte_string += hex(byte)
            byte_string += " "
        for byte in byte_string:
            self.usart.write(byte.encode('utf-8'))
        self.usart.write(b"\n\r")

    def receive_uc(self):
        bytes              = self.usart.read(size = 4)
        self.packet.header = self.packet.deserialize_header(bytes)
        if ( self.packet.header.bits.checksum == self.packet.calculate_checksum()):
            print("Header checksum OK!")
        packet_size  = self.packet.length_hash_table[self.packet.header.bits.length]
        bytes       += self.usart.read(size = (packet_size + 2))
        if self.packet.crc16_calculate(bytes) == 0:
            print("Packet crc16 check OK!")
        self.packet.data.clear()
        self.packet.data  = self.packet.deserialize_data(bytes[4:(len(bytes) - 2)])
        self.packet.crc16 = bytes[(len(bytes) - 2):]

    def receive_socat(self):
        pass


updater = dfu_updater()
updater.print_arguments()

updater.readelf_get_sections(updater.text)

updater.text.calculate_size()
updater.text.convert_to_little_endian()
updater.packet.crc16_lookup_table_generate(0x1021)
updater.init()
# print(updater.text.converted_hexdata)
# print(hex(updater.text.size))
# print(hex(int(updater.text.size / 32)))
# print(hex(updater.text.size % 32))

# updater.packet.create(opcode = 0x00, length = 0x00, packet_number = 0x00, data = [0xaa] * 32)
# updater.packet.serialize()
# updater.packet.print_serialized()

updater.receive_uc()

'''
last_packet_padding = updater.text.size % 32
for packet_number in range(0, int(updater.text.size / 32)):
    updater.packet.create(opcode = DUST_OPCODE.DATA.value,
                          length = DUST_LENGTH.BYTES32.value,
                          packet_number = packet_number,
                          data = [int(hex, 16) for hex in updater.text.converted_hexdata[(packet_number * 32):((packet_number * 32) + 32)]])
    updater.packet.serialize()
    updater.packet.print_serialized()
    print("")
'''
