import json
import os


def generate_signals_source(data):
    # Define file path and open file for writing
    source_file_path = os.path.join("Output/src", "signals.cpp")
    source_file = open(source_file_path, "w")

    # Include the header file
    source_file.write("#include \"signals.h\"\n\n")

    # Write constructor implementation
    source_file.write(
        "CAN_signals::CAN_signals() {\n    // constructor implementation\n}\n\n")

    # Write getter and setter implementations for each signal
    for signal in data["signals"]:
        source_file.write("float CAN_signals::get_{}() {{\n    return m_{};\n}}\n\n".format(
            signal["name"], signal["name"]))
        source_file.write("void CAN_signals::set_{}(float newValue) {{\n    m_{} = newValue;\n}}\n\n".format(
            signal["name"], signal["name"]))

    # Declare private variables for storing signal values
    source_file.write("private:\n")
    for signal in data["signals"]:
        source_file.write("float m_{};\n".format(signal["name"]))

    # Close file
    source_file.close()


def generate_signals_header(data):
    # Define file path and open file for writing
    header_file_path = os.path.join("Output/include/can_messages", "signals.h")
    header_file = open(header_file_path, "w")

    # Define constant values
    ifndef_define = "#ifndef SIGNALS_H"
    define = "#define SIGNALS_H"
    endif = "#endif"
    header_file.write("{}\n{}\n\n".format(ifndef_define, define))

    # Write class definition
    header_file.write("class CAN_signals {\npublic:\n")
    header_file.write("\tCAN_signals();\n")

    # Write getter and setter prototypes for each signal
    for signal in data["signals"]:
        header_file.write("\tfloat get_{}();\n".format(signal["name"]))
        header_file.write("\tvoid set_{}(float newValue);\n".format(
            signal["name"]))

    header_file.write("\nprivate:\n")
    for signal in data["signals"]:
        header_file.write("\tfloat m_{};\n".format(signal["name"]))

    header_file.write("};\n")
    header_file.write("{}\n".format(endif))
    header_file.close()

    # Read JSON data from a file
data = json.load(open("signals.json"))

# Generate header and source files
generate_signals_header(data)
generate_signals_source(data)
