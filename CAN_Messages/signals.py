import json
import sys
import os

# Creating variables
output_directory = 'Output/include/can_messages'
header_file_path = 'Output/include/can_messages'
file_name = 'signals'
file_path = 'signals.json'
file = "signals.h"


def check_file_path(file_path):
    if not file_path:
        print("Error: No file path provided.")
        sys.exit(1)


def open_json(file_path):
    try:
        with open(file_path, 'r') as f:
            # Load the JSON data from the file
            data = json.load(f)
    except FileNotFoundError:
        print(f"Error: {file_path} not found.")
        sys.exit(1)
    return data


def create_output_directory():
    # check if folder exist if not creates it
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)


def write_header_file_constants(output_header_file):
    # Define constant values
    ifndef_define = "#ifndef SIGNALS_H"
    define = "#define SIGNALS_H"
    # endif = "#endif /* SIGNALS_H */"

    output_header_file.write("{}\n{}\n".format(ifndef_define, define))


def write_header_file_includes(header_file):
    include = "\n#include<sstream>\n#include<string>\n"
    header_file.write(include)


def write_header_file_class(header_file, data):
    # Define classes used
    can = 'class CAN_signals\n{'
    public = '\n\tpublic: \n'
    private = '\n\tprivate: \n'
    signal = '\t\tCAN_signals();\n'

    # Write class definition
    header_file.write(can + public)
    header_file.write(signal)

    # Write getter and setter prototypes for each signal
    for signal in data[file_name]:
        header_file.write(
            "\t\t/*\n\t\tget {}\n\t\t*/\n".format(signal["name"]))
        header_file.write("\t\tstd::string get_{}();\n".format(signal["name"]))
        header_file.write(
            "\t\t/*\n\t\tset {}\n\t\t*/\n".format(signal["name"]))
        if signal["name"] == "humidity":
            header_file.write(
                "\t\tstd::string set_{}(uint8_t newValue);\n".format(signal["name"]))
        elif signal["name"] == "temperature":
            header_file.write(
                "\t\tstd::string set_{}(float newValue);\n".format(signal["name"]))

    # Write private class functions
    header_file.write(private)
    header_file.write("\t\tuint8_t m_startMsgId;\n")
    for signal in data[file_name]:
        formatted_name = signal["name"].replace(" ", "")
        header_file.write("\t\tuint8_t m_{}GetMsgId;\n".format(formatted_name))
        header_file.write("\t\tuint8_t m_{}SetMsgId;\n".format(formatted_name))


def close_header_file(output_header_file):
    # define constant
    endif = "#endif /* SIGNALS_H */"

    # close header file
    output_header_file.write("};\n\n")
    output_header_file.write("{}\n".format(endif))
    output_header_file.close()


def generate_signals_source(data):
    # check if folder exist if not creates it
    if not os.path.exists('Output/src'):
        os.makedirs('Output/src')

    # Define file path and open file for writing
    source_file_path = os.path.join('Output/src', file_name + '.cpp')
    source_file = open(source_file_path, "w")

    # Define constant values
    header_include = '#include \"signals.h\"\n\n'

    # Include the header file
    source_file.write(header_include)

    # Write constructor implementation
    source_file.write(
        "CAN_signals::CAN_signals() {\n\tm_startMsgId = 100;\n\tm_temperatureGetMsgId = m_startMsgId + 2;\n\tm_temperatureSetMsgId = m_startMsgId + 2 + 1;\n\tm_humidityGetMsgId = m_startMsgId + 4;\n\tm_humiditySetMsgId = m_startMsgId + 4 + 1;\n}\n\n")

    # Write getter and setter implementations for each signal
    for signal in data["signals"]:
        formatted_name = signal["name"].replace(" ", "")
        source_file.write("std::string CAN_signals::get_{}() {{\n\tstd::stringstream sstream;\n\tsstream << \"{{\\\"ID\\\": \" << m_{}GetMsgId\n\t\t\t\t<< \", \\\"length\\\":0 \"\n\t\t\t\t<< \",  \\\"value\\\": \\\"\\\" }}\";\n\treturn sstream.str();\n}}\n\n".format(
            formatted_name, formatted_name))

        if signal["name"] == "humidity":

            source_file.write("std::string CAN_signals::set_{}(uint8_t newValue) {{\n\tstd::stringstream sstream;\n\tsstream << \"{{\\\"ID\\\": \" << m_{}SetMsgId\n\t\t\t\t<< \", \\\"length\\\":10 \"\n\t\t\t\t<< \", \\\"value\\\": \\\"\" << newValue << \"\\\" }}\";\n\treturn sstream.str();\n}}\n".format(
                formatted_name, formatted_name))

        elif signal["name"] == "temperature":

            source_file.write("std::string CAN_signals::set_{}(float newValue) {{\n\tstd::stringstream sstream;\n\tsstream << \"{{\\\"ID\\\": \" << m_{}SetMsgId\n\t\t\t\t<< \", \\\"length\\\":10 \"\n\t\t\t\t<< \", \\\"value\\\": \\\"\" << newValue << \"\\\" }}\";\n\treturn sstream.str();\n}}\n\n".format(
                formatted_name, formatted_name))

    source_file.close()


def main():
    global header_file_path, file_name
    data = {file_name: [{"name": "temperature"}, {"name": "humidity"}]}
    header_file_path = os.path.join(
        header_file_path, file_name + '.h')
    output_header_file = open(header_file_path, "w")

    # Check file path
    check_file_path(file_path)

    # Open json file
    open_json(file_path)

    # Create Output directory
    create_output_directory()

    # generate_signals_header(data)
    write_header_file_constants(output_header_file)
    write_header_file_includes(output_header_file)
    write_header_file_class(output_header_file, data)

    # Close Header file
    close_header_file(output_header_file)

    generate_signals_source(data)


if __name__ == '__main__':
    main()
