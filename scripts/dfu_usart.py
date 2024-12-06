import sys
import serial

from elftools.elf.elffile import ELFFile

class dfu_updater_segment:
    def __init__(self, name, sections):
        self.name              = name
        self.sections          = sections
        self.size              = 0
        self.raw_hexdata       = []
        self.converted_hexdata = []

    def align4(self):
        addition_bytes = self.size % 4
        self.size = self.size + (4 - addition_bytes)

    def calculate_size(self):
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
    def __init__(self):
        if ( len(sys.argv) < 4 ):
            print("Invalid usage: python3 dfu_usart.py <bin> <port> <baudrate>")
            sys.exit()
        self.bin               = sys.argv[1]
        self.port              = sys.argv[2]
        self.baudrate          = sys.argv[3]
        self.text              = dfu_updater_segment(name = '.text', sections = [])

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

# byte = usart.read(size=1)
# print(byte)

# usart.close()
