import ctypes

c_uint32 = ctypes.c_uint32

class dust_header_bits(ctypes.BigEndianStructure):
    """Documentation for dust_header_bits structure.

    More details.
    """

    _fields_ = [("opcode", c_uint32, 2),
                ("length", c_uint32, 2),
                ("packet_number", c_uint32, 12),
                ("checksum", c_uint32, 16)]


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
        self.crc8               = 0
        self.crc8_lookup_table  = []
        self.crc16              = 0
        self.crc16_lookup_table = []

    def calculate_checksum(self):
        checksum = (self.header.bits.opcode << 14 |
                    self.header.bits.length << 12 |
                    self.header.bits.packet_number << 0)
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
        crc16       = 0x00
        for byte in data:
            position = ((crc16 >> 8) ^ byte) & 0xff
            crc16    = ((crc16 << 8) ^ self.crc16_lookup_table[position]) & 0xffff
        return crc16

    def create(self, opcode, length, packet_number, data):
        self.header.bits.opcode        = opcode
        self.header.bits.length        = length
        self.header.bits.packet_number = packet_number
        self.header.bits.checksum      = self.calculate_checksum()
        self.data                      = data

    def serialize(self):
        self.serialized.clear()
        self.serialized.append((self.header.whole_value & 0xff000000) >> 0x18)
        self.serialized.append((self.header.whole_value & 0x00ff0000) >> 0x10)
        self.serialized.append((self.header.whole_value & 0x0000ff00) >> 0x08)
        self.serialized.append((self.header.whole_value & 0x000000ff) >> 0x00)
        for byte in self.data:
            self.serialized.append(byte)
        self.crc16 = self.crc16_calculate(self.serialized)
        self.serialized.append((self.crc16 & 0xff00) >> 0x08)
        self.serialized.append((self.crc16 & 0x00ff) >> 0x00)

    def deserialize(self, data):
        if self.crc16_calculate(data) == 0:
            print("OK!")
        else:
            print("WRONG!!!")

    def print_packet(self):
        print("opcode:        " + str(f"{self.header.bits.opcode:#x}"))
        print("length:        " + str(f"{self.header.bits.length:#x}"))
        print("packet_number: " + str(f"{self.header.bits.packet_number:#x}"))
        print("checksum:      " + str(f"{self.header.bits.checksum:#x}"))
        print("data:          " + str(' '.join(f"{hex:#x}" for hex in self.data)))
        print("whole_value:   " + str(f"{self.header.whole_value:#x}"))
        print("serialized:    " + str(' '.join(f"{hex:#x}" for hex in self.serialized)))

