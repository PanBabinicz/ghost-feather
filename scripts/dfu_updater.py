import sys
import serial
import dust_packet
import dfu_updater_segment

from elftools.elf.elffile import ELFFile

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
        self.text     = dfu_updater_segment.dfu_updater_segment(name = '.text', sections = [])
        self.packet   = dust_packet.dust_packet()
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
        byte_string = ""
        for byte in self.packet.serialized:
            byte_string += hex(byte)
            byte_string += " "
        for byte in byte_string:
            self.usart.write(byte.encode('utf-8'))
        self.usart.write(b"\n\r")

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
