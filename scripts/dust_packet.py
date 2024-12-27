import ctypes

from enum import Enum

DUST_PACKET_HEADER_SIZE = 4
DUST_PACKET_CRC16_SIZE  = 2

c_uint32 = ctypes.c_uint32

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


class dust_packet:
    """Documentation for dust_packet class.

    More details.
    """

    def __init__(self):
        self.header             = dust_header()
        self.data               = []
        self.serialized         = []
        self.crc16              = 0
        self.crc16_lookup_table = []
        self.length_hash_table  = { DUST_LENGTH.BYTES32.value:  0x20,
                                    DUST_LENGTH.BYTES64.value:  0x40,
                                    DUST_LENGTH.BYTES128.value: 0x80,
                                    DUST_LENGTH.BYTES256.value: 0x100 }

    def calculate_checksum(self):
        checksum = (self.header.bits.opcode        << 0x0e |
                    self.header.bits.length        << 0x0c |
                    self.header.bits.ack           << 0x0b |
                    self.header.bits.packet_number << 0x00)
        checksum = ~(checksum) & 0xffff
        return checksum

    def crc8_lookup_table_generate(self, polynomial):
        for i in range(0, 2**8):
            byte = i
            for b in range(0, 8):
                if ((byte & 0x80) != 0):
                    byte = byte << 1
                    byte = byte ^ polynomial
                else:
                    byte = byte << 1
            self.crc8_lookup_table.append(byte & 0xff)

    def crc8_calculate(self):
        self.crc8 = 0x00
        for byte in self.serialized:
            position = self.crc8 ^ byte
            self.crc8 = self.crc8_lookup_table[position]

    def crc16_lookup_table_generate(self, polynomial):
        for i in range(0, 2**8):
            byte = i << 8
            for b in range(0, 8):
                if ((byte & 0x8000) != 0):
                    byte = byte << 1
                    byte = byte ^ polynomial
                else:
                    byte = byte << 1
            self.crc16_lookup_table.append(byte & 0xffff)

    def crc16_calculate(self, data):
        crc16 = 0x00
        for byte in data:
            position = ((crc16 >> 8) ^ byte) & 0xff
            crc16    = ((crc16 << 8) ^ self.crc16_lookup_table[position]) & 0xffff
        return crc16

    def create(self, opcode, length, ack, packet_number, data):
        self.header.bits.opcode        = opcode
        self.header.bits.length        = length
        self.header.bits.ack           = ack
        self.header.bits.packet_number = packet_number
        self.header.bits.checksum      = self.calculate_checksum()
        self.data                      = data

    def serialize_header(self):
        serialized_header = []
        serialized_header.append(((self.header.whole_value & 0xff000000) >> 0x18))
        serialized_header.append(((self.header.whole_value & 0x00ff0000) >> 0x10))
        serialized_header.append(((self.header.whole_value & 0x0000ff00) >> 0x08))
        serialized_header.append(((self.header.whole_value & 0x000000ff) >> 0x00))
        return serialized_header

    def deserialize_header(self, serialized_header):
        deserialized_header = dust_header()
        deserialized_header.whole_value |= (serialized_header[0] << 0x18)
        deserialized_header.whole_value |= (serialized_header[1] << 0x10)
        deserialized_header.whole_value |= (serialized_header[2] << 0x08)
        deserialized_header.whole_value |= (serialized_header[3] << 0x00)
        return deserialized_header

    def deserialize_data(self, serialized_data):
        deserialized_data = []
        deserialized_data.extend(serialized_data)
        return deserialized_data

    def serialize(self):
        self.serialized.clear()
        self.serialized.extend(self.serialize_header())
        self.serialized.extend(self.data)
        self.crc16 = self.crc16_calculate(self.serialized)
        self.serialized.append((self.crc16 & 0xff00) >> 0x08)
        self.serialized.append((self.crc16 & 0x00ff) >> 0x00)

    def deserialize(self, usart):
        result           = DUST_RESULT.ERROR.value
        serialized_bytes = usart.read(size = DUST_PACKET_HEADER_SIZE)
        self.header      = self.deserialize_header(serialized_bytes)
        if ( self.header.bits.checksum == self.calculate_checksum()):
            packet_size       = self.length_hash_table[self.header.bits.length]
            serialized_bytes += usart.read(size = (packet_size + DUST_PACKET_CRC16_SIZE))
            if self.crc16_calculate(serialized_bytes) == 0:
                self.data.clear()
                self.data  = self.deserialize_data(serialized_bytes[DUST_PACKET_HEADER_SIZE:(len(serialized_bytes) - DUST_PACKET_CRC16_SIZE)])
                self.crc16 = serialized_bytes[(len(serialized_bytes) - DUST_PACKET_CRC16_SIZE):]
                result     = DUST_RESULT.SUCCESS.value
        return result

    def print_packet(self):
        print("opcode:        " + str(f"{self.header.bits.opcode:#x}"))
        print("length:        " + str(f"{self.header.bits.length:#x}"))
        print("ack:           " + str(f"{self.header.bits.ack:#x}"))
        print("packet_number: " + str(f"{self.header.bits.packet_number:#x}"))
        print("checksum:      " + str(f"{self.header.bits.checksum:#x}"))
        print("data:          " + str(' '.join(f"{hex:#x}" for hex in self.data)))
        print("crc16:         " + str(f"{self.crc16:#x}"))
        print("whole_value:   " + str(f"{self.header.whole_value:#x}"))
        print("serialized:    " + str(' '.join(f"{hex:#x}" for hex in self.serialized)))

    def print_serialized(self):
        print("serialized #" + str(self.header.bits.packet_number) + ": " + str(' '.join(f"{hex:#x}" for hex in self.serialized)))

