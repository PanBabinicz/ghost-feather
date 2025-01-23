class dfu_updater_segment:
    """
    @class dfu_updater_segment
    @brief Represents a segment in the DFU (Device Firmware Update) updater.

    This class provides methods to manage firmware update segments, including
    memory alignment, size calculation, and hex data conversion to little-endian format.
    """

    def __init__(self, name, sections):
        self.name              = name
        self.sections          = sections
        self.size              = None
        self.raw_hexdata       = []
        self.converted_hexdata = []

    def align4(self):
        addition_bytes = self.size % 4
        self.size = self.size + (4 - addition_bytes)

    def calculate_size(self):
        self.size = 0
        for section in self.sections:
            self.size += section.data_size
        self.align4()

    def fill_raw_hexdata(self):
        for section in self.sections:
            data = section.data()
            for byte in data:
                self.raw_hexdata.append(byte)

    def four_byte_convert_to_little_endian(self, four_bytes_segment):
        for hex_byte in reversed(four_bytes_segment):
            self.converted_hexdata.append(hex_byte)

    def convert_to_little_endian(self):
        chunks = []
        for i in range(0, self.size, 4):
            chunks.append(self.raw_hexdata[i:i+4])
        # Check if the last chunk is align
        if len(chunks[-1]) < 4:
            chunks[-1].extend([0] * (4 - len(chunks[-1])))
        for chunk in chunks:
            self.four_byte_convert_to_little_endian(chunk)

    def print_size(self):
        print(self.size)

    def print_raw_hexdata(self):
        for data in self.raw_hexdata:
            print(data)

    def print_converted_hexdata(self):
        for data in self.converted_hexdata:
            print(data)
