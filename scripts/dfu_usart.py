import sys
import serial

class dfu_updater:
    def __init__(self):
        if ( len(sys.argv) < 4 ):
            print("Invalid usage: python3 dfu_usart.py <bin> <port> <baudrate>")
            sys.exit()

        self.bin      = sys.argv[1]
        self.port     = sys.argv[2]
        self.baudrate = sys.argv[3]

    def print_arguments(self):
        print("Bin:      " + self.bin)
        print("Port:     " + self.port)
        print("Baudrate: " + self.baudrate)

    def four_byte_convert_to_little_endian(self, four_bytes_segment):
        swapped = ''.join([four_bytes_segment[i:i+2] for i in range(0, len(four_bytes_segment), 2)][::-1])
        print("0x" + swapped)

    def segment_convert_to_little_endian(self, segment_start, segment_stop):
        for i in range(2*segment_start, 2*segment_stop, 8):
            chunk = hexdata[i:i+8]
            updater.four_byte_convert_to_little_endian(chunk)

# usart    = serial.Serial(port=port, baudrate=baudrate, timeout=None)

updater = dfu_updater()
updater.print_arguments()

with open(updater.bin, 'rb') as bin_file:
    hexdata = bin_file.read().hex()

updater.segment_convert_to_little_endian(0x1000, 0x1498)

# byte = usart.read(size=1)
# print(byte)

# usart.close()
