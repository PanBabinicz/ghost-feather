import sys
import serial

def convert_to_little_endian(four_bytes_segment):
    swapped = ''.join([four_bytes_segment[i:i+2] for i in range(0, len(four_bytes_segment), 2)][::-1])
    print(swapped)

if ( len(sys.argv) < 4 ):
    print("Invalid usage: python3 dfu_usart.py <bin> <port> <baudrate>")
    sys.exit()

bin      = sys.argv[1]
port     = sys.argv[2]
baudrate = sys.argv[3]
# usart    = serial.Serial(port=port, baudrate=baudrate, timeout=None)

print("Bin:      " + bin)
print("Port:     " + port)
print("Baudrate: " + baudrate)

with open(bin, 'rb') as bin_file:
    hexdata = bin_file.read().hex()

print(hexdata[2*0x1000:2*0x1020])

convert_to_little_endian(hexdata[2*0x01000:2*0x01004])

# byte = usart.read(size=1)
# print(byte)

# usart.close()
