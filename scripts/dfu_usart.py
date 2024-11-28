import sys
import serial

if ( len(sys.argv) < 3 ):
    print("Invalid usage: python3 dfu_usart.py <port> <baudrate>")
    sys.exit()

port     = sys.argv[1]
baudrate = sys.argv[2]
usart    = serial.Serial(port=port, baudrate=baudrate, timeout=None)

byte = usart.read(size=1)
print(byte)

usart.close()
