import ctypes
import numpy

from enum import Enum

DUST_PACKET_HEADER_SIZE = 4
DUST_PACKET_CRC16_SIZE  = 2
DUST_CRC16_LUT_SIZE     = 256

c_uint8  = ctypes.c_uint8
c_uint16 = ctypes.c_uint16
c_uint32 = ctypes.c_uint32

"""Documentation for dust_crc16_lut.

More details.
"""
dust_crc16_lut = numpy.zeros(DUST_CRC16_LUT_SIZE, dtype=numpy.uint16)


"""Documentation for dust_crc16_generate_lut.

More details.
"""
def dust_crc16_generate_lut(polynomial):
    global dust_crc16_lut
    for i in range(0, 2**8):
        byte = i << 8
        for b in range(0, 8):
            if ((byte & 0x8000) != 0):
                byte = byte << 1
                byte = byte ^ polynomial
            else:
                byte = byte << 1
        dust_crc16_lut[i] = byte & 0xffff


class DUST_RESULT(Enum):
    """Documentation for DUST_RESULT enum.

    More details.
    """

    SUCCESS  = 0x00
    ERROR    = 0x01


class DUST_OPCODE(Enum):
    """Documentation for DUST_OPCODE enum.

    More details.
    """

    CONNECT    = 0x00
    DISCONNECT = 0x01
    DATA       = 0x02
    ERROR      = 0x03


class DUST_LENGTH(Enum):
    """Documentation for DUST_LENGTH enum.

    More details.
    """

    BYTES32  = 0x00
    BYTES64  = 0x01
    BYTES128 = 0x02
    BYTES256 = 0x03


class DUST_ACK(Enum):
    """Documentation for DUST_ACK enum.

    More details.
    """

    UNSET  = 0x00
    SET    = 0x01


class DUST_ACK_FREQUENCY(Enum):
    """Documentation for DUST_ACK_FREQUENCY enum.

    More details.
    """

    AFTER_EACH_PACKET = 0x00
    AFTER_8_PACKETS   = 0x01
    AFTER_16_PACKETS  = 0x02
    AFTER_32_PACKETS  = 0x03
    AFTER_64_PACKETS  = 0x04
    AFTER_128_PACKETS = 0x05
    AFTER_256_PACKETS = 0x06
    AFTER_512_PACKETS = 0x07


class dust_header_bits(ctypes.BigEndianStructure):
    """Documentation for dust_header_bits structure.

    More details.
    """

    _fields_ = [("opcode",        c_uint32, 2),
                ("length",        c_uint32, 2),
                ("ack",           c_uint32, 1),
                ("packet_number", c_uint32, 11),
                ("checksum",      c_uint32, 16)]


class dust_header(ctypes.BigEndianUnion):
    """Documentation for dust_header union.

    More details.
    """

    _fields_ = [("bits", dust_header_bits),
                ("whole_value", c_uint32)]

    def __init__(self):
        self.whole_value = 0

    def calculate_checksum(self):
        checksum = 0
        checksum = (self.bits.opcode        << 0x0e
                 |  self.bits.length        << 0x0c
                 |  self.bits.ack           << 0x0b
                 |  self.bits.packet_number << 0x00)
        checksum = ~(checksum) & 0xffff
        return checksum

    def create(self, opcode, length, ack, packet_number):
        self.bits.opcode        = opcode
        self.bits.length        = length
        self.bits.ack           = ack
        self.bits.packet_number = packet_number
        self.bits.checksum      = self.calculate_checksum()

    def serialize(self):
        serialized_header = []
        serialized_header.append(((self.whole_value & 0xff000000) >> 0x18))
        serialized_header.append(((self.whole_value & 0x00ff0000) >> 0x10))
        serialized_header.append(((self.whole_value & 0x0000ff00) >> 0x08))
        serialized_header.append(((self.whole_value & 0x000000ff) >> 0x00))
        return serialized_header

    def deserialize(self, serialized_header):
        self.whole_value  = 0
        self.whole_value |= (serialized_header[0] << 0x18)
        self.whole_value |= (serialized_header[1] << 0x10)
        self.whole_value |= (serialized_header[2] << 0x08)
        self.whole_value |= (serialized_header[3] << 0x00)


class dust_payload:
    """Documentation for dust_packet class.

    More details.
    """

    def __init__(self):
        self.buffer      = []
        self.buffer_size = 0

    def calculate_size(self):
        self.buffer_size = len(self.buffer)

    def create(self, buffer):
        self.buffer = buffer
        self.calculate_size()

    def serialize(self):
        return self.buffer

    def deserialize(self, serialized_payload):
        self.buffer = serialized_payload


class dust_packet:
    """Documentation for dust_packet class.

    More details.
    """

    def __init__(self):
        self.header  = dust_header()
        self.payload = dust_payload()
        self.crc16   = 0

    def crc16_calculate(self, data):
        global dust_crc16_lut
        crc16 = 0x00
        for byte in data:
            position = ((crc16 >> 8) ^ byte) & 0xff
            crc16    = ((crc16 << 8) ^ dust_crc16_lut[position]) & 0xffff
        return int(crc16)

    def create(self, header, payload):
        data         = []
        self.header  = header
        self.payload = payload
        data += self.header.serialize()
        data += self.payload.serialize()
        self.crc16 = self.crc16_calculate(data)

    def serialize(self):
        serialized_packet = []
        serialized_packet.clear()
        serialized_packet += self.header.serialize()
        serialized_packet += self.payload.serialize()
        serialized_packet.append((self.crc16 & 0xff00) >> 0x08)
        serialized_packet.append((self.crc16 & 0x00ff) >> 0x00)
        return serialized_packet

    def deserialize(self, serialized_data):
        self.header.deserialize(serialized_data)
        self.payload.deserialize(serialized_data[DUST_PACKET_HEADER_SIZE:(len(serialized_data) - DUST_PACKET_CRC16_SIZE)])
        if self.crc16_calculate(serialized_data) != 0:
            return DUST_RESULT.ERROR.value
        self.crc16  = 0
        self.crc16 |= serialized_data[(len(serialized_data) - DUST_PACKET_CRC16_SIZE)]     << 0x08
        self.crc16 |= serialized_data[(len(serialized_data) - DUST_PACKET_CRC16_SIZE + 1)] << 0x00
        return DUST_RESULT.SUCCESS.value


class dust_handshake_options(ctypes.BigEndianStructure):
    """Documentation for dust_handshake_options structure.

    More details.
    """

    _fields_ = [("ack_frequency",     c_uint8),
                ("number_of_packets", c_uint32),
                ("payload_size",      c_uint16)]

    def __init__(self):
        self.ack_frequency     = 0
        self.number_of_packets = 0
        self.payload_size      = 0

    def create(self, ack_frequency, number_of_packets, payload_size):
        self.ack_frequency     = ack_frequency
        self.number_of_packets = number_of_packets
        self.payload_size      = payload_size

    def serialize(self):
        serialized_options = []
        serialized_options.append(self.ack_frequency)
        serialized_options.append(((self.number_of_packets & 0xff000000) >> 0x18))
        serialized_options.append(((self.number_of_packets & 0x00ff0000) >> 0x10))
        serialized_options.append(((self.number_of_packets & 0x0000ff00) >> 0x08))
        serialized_options.append(((self.number_of_packets & 0x000000ff) >> 0x00))
        serialized_options.append(((self.payload_size & 0xff00) >> 0x08))
        serialized_options.append(((self.payload_size & 0x00ff) >> 0x00))
        serialized_options.extend([0x00]*25)
        return serialized_options


class dust_serialized:
    """Documentation for dust_serialized class.

    More details.
    """

    def __init__(self):
        self.buffer      = []
        self.buffer_size = 0

    def calculate_size(self):
        self.buffer_size = len(self.buffer)

    def create(self, buffer):
        self.buffer = buffer
        self.calculate_size()


class dust_instance:
    """Documentation for dust_instance class.

    More details.
    """

    def __init__(self):
        self.options     = dust_handshake_options()
        self.packet      = dust_packet()
        self.serialized  = dust_serialized()

    def print_options(self):
        print("ack_frequency:     " + str(f"{self.options.ack_frequency:#x}"))
        print("number_of_packets: " + str(f"{self.options.number_of_packets:#x}"))
        print("payload_size:      " + str(f"{self.options.payload_size:#x}"))

    def print_packet(self):
        print("opcode:        " + str(f"{self.packet.header.bits.opcode:#x}"))
        print("length:        " + str(f"{self.packet.header.bits.length:#x}"))
        print("ack:           " + str(f"{self.packet.header.bits.ack:#x}"))
        print("packet_number: " + str(f"{self.packet.header.bits.packet_number:#x}"))
        print("checksum:      " + str(f"{self.packet.header.bits.checksum:#x}"))
        print("whole_value:   " + str(f"{self.packet.header.whole_value:#x}"))
        print("data:          " + str(' '.join(f"{hex:#x}" for hex in self.packet.payload.buffer)))
        print("crc16:         " + str(f"{self.packet.crc16:#x}"))

    def print_serialized(self):
        print("serialized #" + str(self.packet.header.bits.packet_number) + ": " + str(' '.join(f"{hex:02x}" for hex in self.serialized.buffer)))
