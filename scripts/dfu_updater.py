import sys
import serial
import time

from elftools.elf.elffile import ELFFile

from dust_packet import dust_packet
from dust_packet import dust_header
from dust_packet import dust_handshake_options
from dust_packet import DUST_RESULT
from dust_packet import DUST_OPCODE
from dust_packet import DUST_LENGTH
from dust_packet import DUST_ACK
from dust_packet import DUST_PACKET_HEADER_SIZE
from dust_packet import DUST_PACKET_CRC16_SIZE

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
        self.options  = dust_handshake_options()
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
            self.packet.create(opcode = DUST_OPCODE.CONNECT.value, length = DUST_LENGTH.BYTES32.value,
                               ack = DUST_ACK.UNSET.value, packet_number = 0x00, data=[0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x20] + [0x00] * 25)
            self.packet.serialize()
            self.transmit_packet()
            result = self.receive_ack()
            if result == DUST_RESULT.SUCCESS.value:
                print("Connected")
        else:
            print("Usart is not initialized...")

    def disconnect(self):
        if isinstance(self.usart, serial.Serial):
            print("Trying to disconnect...")
            self.packet.create(opcode = DUST_OPCODE.DISCONNECT.value, length = DUST_LENGTH.BYTES32.value,
                               ack = DUST_ACK.UNSET.value, packet_number = 0x00, data=[0x00] * 32)
            self.packet.serialize()
            #self.transmit_packet()
            result = self.receive_ack()
            if result == DUST_RESULT.SUCCESS.value:
                print("Disconnected")
        else:
            print("Usart is not initialized...")

    def update(self):
        if isinstance(self.usart, serial.Serial):
            print("Trying to update...")
            number_of_packets
            self.packet.create(opcode = DUST_OPCODE.DISCONNECT.value, length = DUST_LENGTH.BYTES32.value,
                               ack = DUST_ACK.UNSET.value, packet_number = 0x00, data=[0x00] * 32)
            self.packet.serialize()
            #self.transmit_packet()
            result = self.receive_ack()
            if result == DUST_RESULT.SUCCESS.value:
                print("Updated")
        else:
            print("Usart is not initialized...")


    def transmit_packet(self):
        for byte in self.packet.serialized:
            self.usart.write(byte.to_bytes(1, byteorder = 'big'))

    def transmit_socat(self):
        byte_string = ""
        for byte in self.packet.serialized:
            byte_string += hex(byte)
            byte_string += " "
        for byte in byte_string:
            self.usart.write(byte.encode('utf-8'))
        self.usart.write(b"\n\r")

    def receive_ack(self):
        result             = DUST_RESULT.ERROR.value
        data               = self.usart.read(size = DUST_PACKET_HEADER_SIZE)
        self.packet.header = self.packet.deserialize_header(data)
        if (self.packet.header.bits.ack == DUST_ACK.SET.value and
            self.packet.header.bits.checksum == self.packet.calculate_checksum()):
            result = DUST_RESULT.SUCCESS.value
        return result


updater = dfu_updater()
updater.print_arguments()

updater.readelf_get_sections(updater.text)
updater.text.calculate_size()
updater.text.convert_to_little_endian()
updater.packet.crc16_lookup_table_generate(0x1021)

updater.init()
updater.connect()
#updater.update()
#updater.disconnect()
#updater.deinit()

flag = True
packet_number = 0
# Send without the last packet
while packet_number < int(updater.text.size / 32):
    updater.packet.create(opcode = DUST_OPCODE.DATA.value,
                          length = DUST_LENGTH.BYTES32.value,
                          ack = DUST_ACK.UNSET.value,
                          packet_number = packet_number,
                          data = [hex for hex in updater.text.converted_hexdata[(packet_number * 32):((packet_number * 32) + 32)]])
    updater.packet.serialize()
    if (flag == True and packet_number == 23):
        updater.packet.serialized[8] = 0xff
        flag = False
    updater.transmit_packet()
    if (updater.receive_ack() == DUST_RESULT.SUCCESS.value):
        print("#" + str(packet_number) + ": ACK")
        packet_number += 1
    else:
        print("#" + str(packet_number) + ": NACK")
