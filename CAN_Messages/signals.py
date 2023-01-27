import json
import sys
import os

# Save File Name to a vaiable
file_name = 'signals'

# Save the file  path to a variable
file_path = 'signals.json'

signal_name = 'name'

# Check if file the path is provided
if not file_path:
    print("Error: No file path provided.")
    sys.exit(1)

# Open the JSON file
try:
    with open(file_path, 'r') as f:
        # Load the JSON data from the file
        data = json.load(f)
except FileNotFoundError:
    print(f"Error: {file_path} not found.")
    sys.exit(1)


# Define header file
def generate_signals_header(data):
    # check if folder exist if not creates it
    if not os.path.exists('Output/include/can_messages'):
        os.makedirs('Output/include/can_messages')

    # Define file path and open file for writing
    header_file_path = os.path.join(
        'Output/include/can_messages', file_name + '.h')
    header_file = open(header_file_path, "w")

    # Define constant values
    ifndef_define = "#ifndef SIGNALS_H"
    define = "#define SIGNALS_H"
    endif = "#endif /* SIGNALS_H */\n"
    include = "\n#include<sstream>\n#include<string>\n"

    header_file.write("{}\n{}\n{}\n".format(ifndef_define, define, include))

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
        header_file.write(
            "\t\tstd::string set_{}(float newValue);\n".format(signal["name"]))

    header_file.write(private)
    header_file.write("\t\tuint8_t m_startMsgId;\n")
    for signal in data[file_name]:
        formatted_name = signal["name"].replace(" ", "")
        header_file.write("\t\tuint8_t m_{}GetMsgId;\n".format(formatted_name))
        header_file.write("\t\tuint8_t m_{}SetMsgId;\n".format(formatted_name))

    header_file.write("};\n\n")
    header_file.write("{}\n".format(endif))
    header_file.close()


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
        source_file.write("std::string CAN_signals::set_{}(float newValue) {{\n\tstd::stringstream sstream;\n\tsstream << \"{{\\\"ID\\\": \" << m_{}SetMsgId\n\t\t\t\t<< \", \\\"length\\\":10 \"\n\t\t\t\t<< \", \\\"value\\\": \\\"\" << newValue << \"\\\" }}\";\n\treturn sstream.str();\n}}\n\n".format(
            formatted_name, formatted_name))
    source_file.close()


data = {file_name: [{"name": "temperature"}, {"name": "humidity   "}]}
file_name = "signals"

generate_signals_header(data)
generate_signals_source(data)
