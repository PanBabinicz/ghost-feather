import sys
import serial
import ctypes

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
        self.header = dust_header()
        self.data   = []
        self.crc    = None

    def calculate_checksum(self):
        checksum = (self.header.bits.opcode << 14 |
                    self.header.bits.length << 12 |
                    self.header.bits.packet_number << 0)
        checksum = ~(checksum) & 0xffff
        return checksum

    def calculate_crc(self):
        return 1

    def create(self, opcode, length, packet_number, data):
        self.header.bits.opcode        = opcode
        self.header.bits.length        = length
        self.header.bits.packet_number = packet_number
        self.header.bits.checksum      = self.calculate_checksum()
        self.data                      = data
        self.crc                       = self.calculate_crc()

    def print_packet(self):
        print("opcode: " + str(self.header.bits.opcode))
        print("length: " + str(self.header.bits.length))
        print("packet_number: " + str(self.header.bits.packet_number))
        print("checksum: " + str(hex(self.header.bits.checksum)))
        print("data: " + str(self.data))
        print("crc: " + str(self.crc))
        print("whole_value: " + str(self.header.whole_value))
        self.calculate_checksum()


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


# usart    = serial.Serial(port=port, baudrate=baudrate, timeout=None)

updater = dfu_updater()
updater.print_arguments()

updater.readelf_get_sections(updater.text)

updater.text.calculate_size()
updater.text.convert_to_little_endian()

updater.packet.create(opcode = 1, length = 1, packet_number = 1, data = [1, 2, 3])
updater.packet.print_packet()

# byte = usart.read(size=1)
# print(byte)

# usart.close()
