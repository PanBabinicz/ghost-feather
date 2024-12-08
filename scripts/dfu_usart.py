import sys
import serial
import ctypes

from elftools.elf.elffile import ELFFile

c_uint32 = ctypes.c_uint32

class dust_header(ctypes.BigEndianStructure):
    _fields_ = [("opcode", c_uint32, 2),
                ("length", c_uint32, 2),
                ("packet_number", c_uint32, 12),
                ("checksum", c_uint32, 16)]


class dfu_updater_segment:
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


class dfu_updater_packet:
    def __init__(self):
        self.header = dust_header()

    def print_header(self):
        print(self.header.opcode)

    def create_header(self, opcode, length, packet_number, checksum):
        self.opcode = (opcode & self.opcode_mask) << 13
        self.length = (length & self.length_mask) << 11
        self.packet_number = (packet_number & self.packet_number_mask)
        pass

    def send(self):
        pass

    def receive(self):
        pass


class dfu_updater:
    def __init__(self):
        if ( len(sys.argv) < 4 ):
            print("Invalid usage: python3 dfu_usart.py <bin> <port> <baudrate>")
            sys.exit()
        self.bin               = sys.argv[1]
        self.port              = sys.argv[2]
        self.baudrate          = sys.argv[3]
        self.text              = dfu_updater_segment(name = '.text', sections = [])
        self.packet            = dfu_updater_packet()

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
updater.packet.print_header()

# byte = usart.read(size=1)
# print(byte)

# usart.close()
