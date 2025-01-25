import ctypes
import numpy

from enum import Enum

DUST_PACKET_HEADER_SIZE = 4
DUST_PACKET_CRC16_SIZE  = 2
DUST_CRC16_LUT_SIZE     = 256

c_uint8  = ctypes.c_uint8
c_uint16 = ctypes.c_uint16
c_uint32 = ctypes.c_uint32

"""
@brief Lookup table for CRC-16 calculation.

This table stores precomputed CRC-16 values for efficiency. The table is generated using
the `dust_crc16_generate_lut` function and the provided polynomial.
"""
dust_crc16_lut = numpy.zeros(DUST_CRC16_LUT_SIZE, dtype=numpy.uint16)


def dust_crc16_generate_lut(polynomial):
    """
    @brief Generates a lookup table for CRC-16 calculations.

    This function computes a CRC-16 lookup table using the specified polynomial. The table
    is used to accelerate CRC-16 calculations during runtime.

    @param polynomial The polynomial used for CRC-16 calculations (e.g., 0x1021).
    """
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
    """
    @brief Enum for DUST_RESULT.

    Defines the possible results of dust protocol operations.
    """
    SUCCESS  = 0x00
    ERROR    = 0x01


class DUST_OPCODE(Enum):
    """
    @brief Enum for DUST_OPCODE.

    Represents the opcodes used in dust protocol packets.
    """
    CONNECT    = 0x00
    DISCONNECT = 0x01
    DATA       = 0x02
    ERROR      = 0x03


class DUST_LENGTH(Enum):
    """
    @brief Enum for DUST_LENGTH.

    Specifies the lengths of payloads used in dust protocol packets.
    """
    BYTES32  = 0x00
    BYTES64  = 0x01
    BYTES128 = 0x02
    BYTES256 = 0x03


class DUST_ACK(Enum):
    """
    @brief Enum for DUST_ACK.

    Defines the acknowledgment status in dust protocol packets.
    """
    UNSET  = 0x00
    SET    = 0x01


class DUST_ACK_FREQUENCY(Enum):
    """
    @brief Enum for DUST_ACK_FREQUENCY.

    Specifies how often acknowledgments are sent during data transmission in the dust protocol.
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
    """
    @brief Structure representing the individual bits of a dust header.

    This structure defines the bit fields for the dust protocol header, allowing easy access
    to individual components such as opcode, length, acknowledgment flag, packet number, and checksum.
    """
    _fields_ = [("opcode",        c_uint32, 2),
                ("length",        c_uint32, 2),
                ("ack",           c_uint32, 1),
                ("packet_number", c_uint32, 11),
                ("checksum",      c_uint32, 16)]


class dust_header(ctypes.BigEndianUnion):
    """
    @brief Union representing a dust header.

    This union allows the dust header to be accessed either as individual bit fields
    (using the `dust_header_bits` structure) or as a single 32-bit value (`whole_value`).
    """
    _fields_ = [("bits", dust_header_bits),
                ("whole_value", c_uint32)]

    def __init__(self):
        """
        @brief Initializes the dust header.

        Sets the `whole_value` to 0, effectively clearing all fields.
        """
        self.whole_value = 0

    def calculate_checksum(self):
        """
        @brief Calculates the checksum for the dust header.

        Combines the opcode, length, acknowledgment flag, and packet number fields to compute
        the checksum, ensuring the header's integrity.

        @return Computed checksum (16 bits).
        """
        checksum = 0
        checksum = (self.bits.opcode        << 0x0e
                 |  self.bits.length        << 0x0c
                 |  self.bits.ack           << 0x0b
                 |  self.bits.packet_number << 0x00)
        checksum = ~(checksum) & 0xffff
        return checksum

    def create(self, opcode, length, ack, packet_number):
        """
        @brief Creates a dust header with the specified parameters.

        Prepares the header fields and computes the checksum.

        @param opcode        Operation code for the header.
        @param length        Payload length.
        @param ack           Acknowledgment flag.
        @param packet_number Packet number.
        """
        self.bits.opcode        = opcode
        self.bits.length        = length
        self.bits.ack           = ack
        self.bits.packet_number = packet_number
        self.bits.checksum      = self.calculate_checksum()

    def serialize(self):
        """
        @brief Serializes the dust header into a byte array.

        Converts the 32-bit `whole_value` into four separate bytes for transmission.

        @return A list of 4 bytes representing the serialized header.
        """
        serialized_header = []
        serialized_header.append(((self.whole_value & 0xff000000) >> 0x18))
        serialized_header.append(((self.whole_value & 0x00ff0000) >> 0x10))
        serialized_header.append(((self.whole_value & 0x0000ff00) >> 0x08))
        serialized_header.append(((self.whole_value & 0x000000ff) >> 0x00))
        return serialized_header

    def deserialize(self, serialized_header):
        """
        @brief Deserializes a byte array into a dust header.

        Populates the `whole_value` field using the serialized byte array.

        @param serialized_header A list of 4 bytes representing the serialized header.
        """
        self.whole_value  = 0
        self.whole_value |= (serialized_header[0] << 0x18)
        self.whole_value |= (serialized_header[1] << 0x10)
        self.whole_value |= (serialized_header[2] << 0x08)
        self.whole_value |= (serialized_header[3] << 0x00)


class dust_payload:
    """
    @brief Class representing the payload of a dust packet.

    This class provides methods for creating, serializing, and deserializing payload data.
    """

    def __init__(self):
        """
        @brief Initializes the payload.

        Sets the buffer to an empty list and the buffer size to 0.
        """
        self.buffer      = []
        self.buffer_size = 0

    def calculate_size(self):
        """
        @brief Calculates the size of the payload.

        Updates the buffer size based on the length of the buffer.
        """
        self.buffer_size = len(self.buffer)

    def create(self, buffer):
        """
        @brief Creates a payload with the specified data.

        Initializes the buffer with the provided data and calculates its size.

        @param buffer List of bytes representing the payload data.
        """
        self.buffer = buffer
        self.calculate_size()

    def serialize(self):
        """
        @brief Serializes the payload data.

        Converts the payload buffer into a byte array for transmission.

        @return A list of bytes representing the serialized payload.
        """
        return self.buffer

    def deserialize(self, serialized_payload):
        """
        @brief Deserializes a byte array into a payload.

        Populates the buffer with the deserialized payload data.

        @param serialized_payload A list of bytes representing the serialized payload.
        """
        self.buffer = serialized_payload


class dust_packet:
    """
    @brief Class representing a dust packet.

    This class provides methods to create, serialize, and deserialize dust packets. Each packet
    consists of a header, a payload, and a CRC16 checksum for data integrity.
    """

    def __init__(self):
        """
        @brief Initializes a dust packet.

        Creates an empty dust packet with a default header, payload, and CRC16 checksum set to 0.
        """
        self.header  = dust_header()
        self.payload = dust_payload()
        self.crc16   = 0

    def crc16_calculate(self, data):
        """
        @brief Calculates the CRC16 checksum for a given data array.

        Uses the dust CRC16 lookup table to compute the checksum.

        @param data A list of bytes representing the data to calculate the CRC16 checksum for.
        @return The computed CRC16 checksum as an integer.
        """
        global dust_crc16_lut
        crc16 = 0x00
        for byte in data:
            position = ((crc16 >> 8) ^ byte) & 0xff
            crc16    = ((crc16 << 8) ^ dust_crc16_lut[position]) & 0xffff
        return int(crc16)

    def create(self, header, payload):
        """
        @brief Creates a dust packet with the given header and payload.

        Combines the serialized header and payload to compute the CRC16 checksum.

        @param header  A `dust_header` object representing the packet header.
        @param payload A `dust_payload` object representing the packet payload.
        """
        data         = []
        self.header  = header
        self.payload = payload
        data += self.header.serialize()
        data += self.payload.serialize()
        self.crc16 = self.crc16_calculate(data)

    def serialize(self):
        """
        @brief Serializes the dust packet into a byte array.

        Combines the serialized header, payload, and CRC16 checksum into a single byte array for transmission.

        @return A list of bytes representing the serialized packet.
        """
        serialized_packet = []
        serialized_packet.clear()
        serialized_packet += self.header.serialize()
        serialized_packet += self.payload.serialize()
        serialized_packet.append((self.crc16 & 0xff00) >> 0x08)
        serialized_packet.append((self.crc16 & 0x00ff) >> 0x00)
        return serialized_packet

    def deserialize(self, serialized_data):
        """
        @brief Deserializes a byte array into a dust packet.

        Populates the header, payload, and CRC16 checksum fields from the serialized data.
        Verifies the integrity of the packet using the CRC16 checksum.

        @param serialized_data A list of bytes representing the serialized packet.
        @return `DUST_RESULT.SUCCESS` If deserialization is successful.
        @return `DUST_RESULT.ERROR`   If the CRC16 checksum fails.
        """
        self.header.deserialize(serialized_data)
        self.payload.deserialize(serialized_data[DUST_PACKET_HEADER_SIZE:(len(serialized_data) - DUST_PACKET_CRC16_SIZE)])
        if self.crc16_calculate(serialized_data) != 0:
            return DUST_RESULT.ERROR.value
        self.crc16  = 0
        self.crc16 |= serialized_data[(len(serialized_data) - DUST_PACKET_CRC16_SIZE)]     << 0x08
        self.crc16 |= serialized_data[(len(serialized_data) - DUST_PACKET_CRC16_SIZE + 1)] << 0x00
        return DUST_RESULT.SUCCESS.value


class dust_handshake_options(ctypes.BigEndianStructure):
    """
    @brief Structure representing dust handshake options.

    This structure contains the settings for the handshake process, including acknowledgment frequency,
    number of packets, and payload size.
    """
    _fields_ = [("ack_frequency",     c_uint8),
                ("number_of_packets", c_uint32),
                ("payload_size",      c_uint16)]

    def __init__(self):
        """
        @brief Initializes the handshake options.

        Sets all fields (`ack_frequency`, `number_of_packets`, and `payload_size`) to 0.
        """
        self.ack_frequency     = 0
        self.number_of_packets = 0
        self.payload_size      = 0

    def create(self, ack_frequency, number_of_packets, payload_size):
        """
        @brief Creates handshake options with the specified parameters.

        @param ack_frequency     The acknowledgment frequency setting.
        @param number_of_packets The total number of packets for the handshake.
        @param payload_size      The size of the payload in bytes.
        """
        self.ack_frequency     = ack_frequency
        self.number_of_packets = number_of_packets
        self.payload_size      = payload_size

    def serialize(self):
        """
        @brief Serializes the handshake options into a byte array.

        Converts the handshake options fields into a list of bytes for transmission.

        @return A list of bytes representing the serialized handshake options.
        """
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
    """
    @brief Class representing serialized data for dust packets.

    This class manages a buffer and its size, providing functionality to create and
    calculate the size of the serialized data.
    """

    def __init__(self):
        """
        @brief Initializes an empty dust serialized object.

        Creates an empty buffer with size set to 0.
        """
        self.buffer      = []
        self.buffer_size = 0

    def calculate_size(self):
        """
        @brief Calculates the size of the buffer.

        Updates the `buffer_size` field to match the current length of the buffer.
        """
        self.buffer_size = len(self.buffer)

    def create(self, buffer):
        """
        @brief Creates the serialized buffer from the given data.

        Assigns the provided buffer and calculates its size.

        @param buffer A list of bytes to populate the serialized buffer.
        """
        self.buffer = buffer
        self.calculate_size()


class dust_instance:
    """
    @brief Class representing a dust instance.

    This class encapsulates the handshake options, packet data, and serialized data for a dust protocol instance.
    """

    def __init__(self):
        """
        @brief Initializes a dust instance.

        Creates default objects for handshake options, packet data, and serialized data.
        """
        self.options     = dust_handshake_options()
        self.packet      = dust_packet()
        self.serialized  = dust_serialized()

    def print_options(self):
        """
        @brief Prints the handshake options of the instance.

        Displays the acknowledgment frequency, number of packets, and payload size in hexadecimal format.
        """
        print("ack_frequency:     " + str(f"{self.options.ack_frequency:#x}"))
        print("number_of_packets: " + str(f"{self.options.number_of_packets:#x}"))
        print("payload_size:      " + str(f"{self.options.payload_size:#x}"))

    def print_packet(self):
        """
        @brief Prints the details of the dust packet.

        Displays the header fields, payload buffer data, and CRC16 checksum in hexadecimal format.
        """
        print("opcode:        " + str(f"{self.packet.header.bits.opcode:#x}"))
        print("length:        " + str(f"{self.packet.header.bits.length:#x}"))
        print("ack:           " + str(f"{self.packet.header.bits.ack:#x}"))
        print("packet_number: " + str(f"{self.packet.header.bits.packet_number:#x}"))
        print("checksum:      " + str(f"{self.packet.header.bits.checksum:#x}"))
        print("whole_value:   " + str(f"{self.packet.header.whole_value:#x}"))
        print("data:          " + str(' '.join(f"{hex:#x}" for hex in self.packet.payload.buffer)))
        print("crc16:         " + str(f"{self.packet.crc16:#x}"))

    def print_serialized(self):
        """
        @brief Prints the serialized representation of the dust packet.

        Displays the serialized data buffer along with the packet number.
        """
        print("serialized #" + str(self.packet.header.bits.packet_number) + ": " + str(' '.join(f"{hex:02x}" for hex in self.serialized.buffer)))
