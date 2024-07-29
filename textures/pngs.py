import glob
import os


def convert_png_to_byte_array(files):
    with open("icons_bytes.h", 'w') as f:
        f.write("#include <array>\n#include <cstdint>\n\n")  # add includes
        for file_path in files:
            print(f"Converting file: {file_path}\n")  # print current file

            with open(file_path, 'rb') as img_file:  # read image file
                byte_array = img_file.read()

            array_name = os.path.basename(file_path).replace('.', '_')
            f.write(f"constexpr static auto {array_name} = std::to_array<uint8_t>({{\n")
            for i, byte in enumerate(byte_array):
                if i != 0 and i % 8 == 0:  # each 8 bytes print new line
                    f.write('\n\t')
                f.write(f"{hex(byte)}, ")
            f.write("\n});\n\n")


current_folder = os.getcwd()
png_files = glob.glob(os.path.join(current_folder, '*.png'))

convert_png_to_byte_array(png_files)
