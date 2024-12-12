import sys
import serial
import ctypes
import time

from elftools.elf.elffile import ELFFile

c_uint32 = ctypes.c_uint32

class dust_header_bits(ctypes.BigEndianStructure):
    """Documentation for dust_header_bits structure.

    More details.
    """

    _fields_ = [("opcode", c_uint32, 2),
                ("length", c_uint32, 2),
                ("packet_number", c_uint32, 12),
                ("checksum", c_uint32, 16)]


class dust_header(ctypes.BigEndianUnion):
    """Documentation for dust_header union.

    More details.
    """

    _fields_ = [("bits", dust_header_bits),
                ("whole_value", c_uint32)]


class dust_packet:
    """Documentation for dust_packet class.

    More details.
    """

    def __init__(self):
        self.header             = dust_header()
        self.data               = []
        self.serialized         = []
        self.crc8               = 0
        self.crc8_lookup_table  = []
        self.crc16              = 0
        self.crc16_lookup_table = []

    def calculate_checksum(self):
        checksum = (self.header.bits.opcode << 14 |
                    self.header.bits.length << 12 |
                    self.header.bits.packet_number << 0)
        checksum = ~(checksum) & 0xffff
        return checksum

    def crc8_lookup_table_generate(self, polynomial):
        for i in range(0, 2**8):
            byte = i
            for b in range(0, 8):
                if ((byte & 0x80) != 0):
                    byte = byte << 1
                    byte = byte ^ polynomial
                else:
                    byte = byte << 1
            self.crc8_lookup_table.append(byte & 0xff)

    def crc8_calculate(self):
        self.crc8 = 0x00
        for byte in self.serialized:
            position = self.crc8 ^ byte
            self.crc8 = self.crc8_lookup_table[position]

    def crc16_lookup_table_generate(self, polynomial):
        for i in range(0, 2**8):
            byte = i << 8
            for b in range(0, 8):
                if ((byte & 0x8000) != 0):
                    byte = byte << 1
                    byte = byte ^ polynomial
                else:
                    byte = byte << 1
            self.crc16_lookup_table.append(byte & 0xffff)

    def crc16_calculate(self, data):
        crc16       = 0x00
        for byte in data:
            position = ((crc16 >> 8) ^ byte) & 0xff
            crc16    = ((crc16 << 8) ^ self.crc16_lookup_table[position]) & 0xffff
        return crc16

    def create(self, opcode, length, packet_number, data):
        self.header.bits.opcode        = opcode
        self.header.bits.length        = length
        self.header.bits.packet_number = packet_number
        self.header.bits.checksum      = self.calculate_checksum()
        self.data                      = data

    def serialize(self):
        self.serialized.clear()
        self.serialized.append((self.header.whole_value & 0xff000000) >> 0x18)
        self.serialized.append((self.header.whole_value & 0x00ff0000) >> 0x10)
        self.serialized.append((self.header.whole_value & 0x0000ff00) >> 0x08)
        self.serialized.append((self.header.whole_value & 0x000000ff) >> 0x00)
        for byte in self.data:
            self.serialized.append(byte)
        self.crc16 = self.crc16_calculate(self.serialized)
        self.serialized.append((self.crc16 & 0xff00) >> 0x08)
        self.serialized.append((self.crc16 & 0x00ff) >> 0x00)

    def deserialize(self, data):
        if self.crc16_calculate(data) == 0:
            print("OK!")
        else:
            print("WRONG!!!")

    def print_packet(self):
        print("opcode:        " + str(f"{self.header.bits.opcode:#x}"))
        print("length:        " + str(f"{self.header.bits.length:#x}"))
        print("packet_number: " + str(f"{self.header.bits.packet_number:#x}"))
        print("checksum:      " + str(f"{self.header.bits.checksum:#x}"))
        print("data:          " + str(' '.join(f"{hex:#x}" for hex in self.data)))
        print("whole_value:   " + str(f"{self.header.whole_value:#x}"))
        print("serialized:    " + str(' '.join(f"{hex:#x}" for hex in self.serialized)))


class dfu_updater_segment:
    """Documentation for dfu_updater_segment class.

    More details.
    """

    def __init__(self, name, sections):
        self.name              = name
        self.sections          = sections
        self.size              = None
        self.raw_hexdata       = []
        self.converted_hexdata = []

    def align4(self):
        addition_bytes = self.size % 4
        self.size = self.size + (4 - addition_bytes)

    def calculate_size(self):
        self.size = 0
        for section in self.sections:
            self.size += section.data_size
        self.align4()

    def get_raw_hexdata(self):
        for section in self.sections:
            data = section.data()
            for byte in data:
                self.raw_hexdata.append(hex(byte))

    def print_size(self):
        print(self.size)

    def print_raw_hexdata(self):
        for data in self.raw_hexdata:
            print(hex(data))

    def print_converted_hexdata(self):
        for data in self.converted_hexdata:
            print(hex(data))

    def four_byte_convert_to_little_endian(self, four_bytes_segment):
        for hex_byte in reversed(four_bytes_segment):
            self.converted_hexdata.append(hex_byte)

    def convert_to_little_endian(self):
        chunks = []
        for i in range(0, self.size, 4):
            chunks.append(self.raw_hexdata[i:i+4])
        # Check if the last chunk is align
        if len(chunks[-1]) < 4:
            chunks[-1].extend([0] * (4 - len(chunks[-1])))
        for chunk in chunks:
            self.four_byte_convert_to_little_endian(chunk)


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
            segment.get_raw_hexdata()

    def init(self):
        if isinstance(self.usart, serial.Serial):
            print("The usart is already initialized...")
        else:
            print("Initializing...")
            self.usart = serial.Serial(port = self.port, baudrate = self.baudrate, timeout = None)
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
            self.packet.create(opcode = 0x00, length = 0x00, packet_number = 0x00, data = [0xCC] * 32)
            self.packet.serialize()
            self.transmit()
            #self.receive()
        else:
            print("Usart is not initialized...")


    def disconnect(self):
        self.packet.create(opcode = 0x01, length = 0x00, packet_number = 0x00, data = [0xDD] * 32)
        self.packet.serialize()
        #self.transmit()
        #self.receive()

    def transmit(self):
        for byte in self.packet.serialized:
            self.usart.write(byte)

    def receive(self):
        pass


# usart    = serial.Serial(port=port, baudrate=baudrate, timeout=None)

updater = dfu_updater()
updater.print_arguments()

updater.readelf_get_sections(updater.text)

updater.text.calculate_size()
updater.text.convert_to_little_endian()

# updater.packet.create(opcode = 0x00, length = 0x00, packet_number = 0x00, data = [0x31, 0x32, 0x33, 0x34, 0x35, 0x36])
# updater.packet.print_packet()
updater.packet.crc16_lookup_table_generate(0x1021)
updater.init()
updater.connect()
updater.packet.print_packet()
updater.packet.deserialize(updater.packet.serialized)
updater.deinit()

# byte = usart.read(size=1)
# print(byte)

# usart.close()
