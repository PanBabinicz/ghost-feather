class dfu_updater_segment:
    """
    @class dfu_updater_segment
    @brief Represents a segment in the DFU (Device Firmware Update) updater.

    This class provides methods to manage firmware update segments, including
    memory alignment, size calculation, and hex data conversion to little-endian format.
    """

    def __init__(self, name, sections):
        """
        @brief Constructor for the dfu_updater_segment class.

        @param name     Name of the segment.
        @param sections List of sections belonging to this segment.
        """
        self.name              = name
        self.sections          = sections
        self.size              = None
        self.raw_hexdata       = []
        self.converted_hexdata = []

    def align4(self):
        """
        @brief Aligns the size of the segment to a multiple of 4 bytes.

        This method adjusts the segment size by adding the necessary padding
        bytes to ensure it is aligned to a 4-byte boundary.
        """
        addition_bytes = self.size % 4
        self.size = self.size + (4 - addition_bytes)

    def calculate_size(self):
        """
        @brief Calculates the total size of the segment.

        Iterates through all sections in the segment, summing their data sizes,
        and ensures the total size is aligned to 4 bytes.
        """
        self.size = 0
        for section in self.sections:
            self.size += section.data_size
        self.align4()

    def fill_raw_hexdata(self):
        """
        @brief Fills the raw hex data from all sections.

        This method extracts the data from each section in the segment and appends
        it to the raw_hexdata list.
        """
        for section in self.sections:
            data = section.data()
            for byte in data:
                self.raw_hexdata.append(byte)

    def four_byte_convert_to_little_endian(self, four_bytes_segment):
        """
        @brief Converts a 4-byte segment to little-endian format.

        @param four_bytes_segment A list of 4 bytes to be converted.
        The bytes are reversed and appended to the converted_hexdata list.
        """
        for hex_byte in reversed(four_bytes_segment):
            self.converted_hexdata.append(hex_byte)

    def convert_to_little_endian(self):
        """
        @brief Converts the entire segment's hex data to little-endian format.

        This method divides the raw hex data into 4-byte chunks, adds padding to the
        last chunk if necessary, and converts each chunk to little-endian format.
        """
        chunks = []
        for i in range(0, self.size, 4):
            chunks.append(self.raw_hexdata[i:i+4])
        # Check if the last chunk is align
        if len(chunks[-1]) < 4:
            chunks[-1].extend([0] * (4 - len(chunks[-1])))
        for chunk in chunks:
            self.four_byte_convert_to_little_endian(chunk)

    def print_size(self):
        """
        @brief Prints the size of the segment.

        This is a debug method to display the calculated size.
        """
        print(self.size)

    def print_raw_hexdata(self):
        """
        @brief Prints the raw hex data.

        This is a debug method to display the raw hex data of the segment.
        """
        for data in self.raw_hexdata:
            print(data)

    def print_converted_hexdata(self):
        """
        @brief Prints the converted hex data in little-endian format.

        This is a debug method to display the hex data after conversion.
        """
        for data in self.converted_hexdata:
            print(data)
