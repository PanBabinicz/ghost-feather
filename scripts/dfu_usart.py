import sys
import serial

from elftools.elf.elffile import ELFFile

class dfu_updater:
    def __init__(self):
        if ( len(sys.argv) < 4 ):
            print("Invalid usage: python3 dfu_usart.py <bin> <port> <baudrate>")
            sys.exit()

        self.bin      = sys.argv[1]
        self.port     = sys.argv[2]
        self.baudrate = sys.argv[3]

        self.converted_hexdata = []
        self.raw_hexdata       = []
        self.text              = []

    def print_arguments(self):
        print("Bin:      " + self.bin)
        print("Port:     " + self.port)
        print("Baudrate: " + self.baudrate)

    def four_byte_convert_to_little_endian(self, four_bytes_segment):
        swapped = ''.join([four_bytes_segment[i:i+2] for i in range(0, len(four_bytes_segment), 2)][::-1])
        return swapped

    def segment_convert_to_little_endian(self, segment_start, segment_stop):
        for i in range(2*segment_start, 2*segment_stop, 8):
            chunk = self.raw_hexdata[i:i+8]
            self.converted_hexdata.append(self.four_byte_convert_to_little_endian(chunk))

    def print_converted_hexdata(self):
        for hexdata in self.converted_hexdata:
            print(hexdata)

    def get_data_from_file(self):
        with open(self.bin, 'rb') as bin_file:
            self.elf = ELFFile(bin_file)

    def readelf_get_sections(self):
        with open(self.bin, 'rb') as bin_file:
            self.elf = ELFFile(bin_file)
            for section in self.elf.iter_sections():
                if (section.name.startswith('.text')):
                    print(section)

"""
        size = 0
        print(self.file.find_sections('.text'))
        for section in self.file.segments[0].sections:
            size += section.size
            print(str(section) + ": " + str(section.size) + " " + str(section.addralign))
        print(size)
"""

# usart    = serial.Serial(port=port, baudrate=baudrate, timeout=None)

updater = dfu_updater()

updater.print_arguments()
# updater.get_data_from_file()
updater.segment_convert_to_little_endian(0x1000, 0x1498)
updater.readelf_get_sections()
# updater.print_converted_hexdata()

# byte = usart.read(size=1)
# print(byte)

# usart.close()
