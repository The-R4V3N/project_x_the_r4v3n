import json
import sys
import os

# Save File Name to a vaiable
file_name = 'signals'

# Save the file  path to a variable
file_path = 'signals.json'

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

# Check if the data is correctly converted
# The data is now a dictionary
# print(data)


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

    header_file.write("{}\n{}\n\n".format(ifndef_define, define))

    # Define classes used
    can = 'class CAN_signals\n{'
    public = '\npublic: \n'
    private = '\nprivate: \n'
    signal = '\tCAN_signals();\n'

    # Write class definition
    header_file.write(can + public)
    header_file.write(signal)

    # Write getter and setter prototypes for each signal
    for signal in data[file_name]:
        header_file.write("\tfloat get_{}();\n".format(signal["name"]))
        header_file.write("\tvoid set_{}(float newValue);\n".format(
            signal["name"]))

    header_file.write(private)
    for signal in data[file_name]:
        header_file.write("\tfloat m_{};\n".format(signal["name"]))

    header_file.write("};\n\n")
    header_file.write("{}\n".format(endif))
    header_file.close()


def generate_signals_source(data):
    # check if folder exist if not creates it
    if not os.path.exists('Output/src'):
        os.makedirs('Output/srcs')

    # Define file path and open file for writing
    source_file_path = os.path.join('Output/src', file_name + '.cpp')
    source_file = open(source_file_path, "w")

    # Define constant values
    header_include = '#include \"signals.h\"\n\n'
    private = "private:\n\n"

    # Include the header file
    source_file.write(header_include)

    # Write constructor implementation
    source_file.write(
        "CAN_signals::CAN_signals() {\n    // constructor implementation\n}\n\n")

    # Write getter and setter implementations for each signal
    for signal in data[file_name]:
        source_file.write("float CAN_signals::get_{}() {{\n    return m_{};\n}}\n\n".format(
            signal["name"], signal["name"]))
        source_file.write("void CAN_signals::set_{}(float newValue) {{\n    m_{} = newValue;\n}}\n\n".format(
            signal["name"], signal["name"]))

    # !Getting an error here in the cpp file. it says expected a declaration but the same code line works in the header file. Cant figure out what is wrong here!!!!!!
    # Declare private variables for storing signal values
    source_file.write(private)
    for signal in data[file_name]:
        source_file.write("\tfloat m_{};\n".format(signal["name"]))

    # Close file
    source_file.close()


generate_signals_header(data)
generate_signals_source(data)
