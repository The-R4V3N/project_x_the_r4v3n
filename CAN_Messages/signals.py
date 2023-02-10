import json
import os


def write_output(output_header_filename, data):

    with open(output_header_filename, "w") as file_fd:
        file_fd.writelines(data)


def create_output_header_directory():
    # check if folder exist if not creates it
    output_directory = os.path.join('Output', 'include', 'can_messages')
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)


def gen_include_guard_class_decl_ctor(input_json_filename):
    top = []  # include guard, class declaration and constructor
    bottom = ""  # ending of include guard

    json_name_upper = input_json_filename.upper()
    include_guard_name = f'HEADER_{json_name_upper}_H'
    include_library_name = f'<sstream>\n#include <string>'

    top.append(f'#ifndef {include_guard_name}')
    top.append(f'#define {include_guard_name}')
    top.append('\n')
    top.append(f'#include {include_library_name}')
    top.append('\n')
    top.append(f'class CAN_{input_json_filename} \n{{')
    top.append('\tpublic:')
    top.append(f'\t\tCAN_{input_json_filename}();')

    bottom = ['};', f'\n#endif //{include_guard_name}\n']
    return top, bottom


def generate_getter_h(signal_name, signal_type, signal_length, signal_comment):
    buffer = f"\t/*\n\tget {signal_comment}\n\t*/\n"
    buffer += f'\tstd::string get_{signal_name}();'
    return buffer


def generate_setter_h(signal_name, signal_type, signal_length, signal_comment):
    buffer = f"\t/*\n\tset {signal_comment}\n\t*/\n"
    buffer += f'\tstd::string set_{signal_name}({signal_type} newValue);'
    return buffer


def generate_get_set_functions(json_dict):
    content = []
    for signal in json_dict["signals"]:
        signal_name = signal["name"]
        signal_type = signal["type"]
        signal_length = signal["length"]
        signal_comment = signal["comment"]
        set_prototype = generate_setter_h(
            signal_name, signal_type, signal_length, signal_comment)
        content.append(set_prototype)
        set_prototype = generate_getter_h(
            signal_name, signal_type, signal_length, signal_comment)
        content.append(set_prototype)
    return content


def generate_private_fields(json_dict):
    content = []
    signal_type = "uint8_t"
    msgid = "MsgId"
    field_start = "\t{} m_start{};".format(signal_type,  msgid)
    content.append(field_start)
    for signal in json_dict["signals"]:
        signal_name = "m_" + signal["name"]
        field_get = "\t{} {}Get{};".format(signal_type, signal_name, msgid)
        field_set = "\t{} {}Set{};".format(signal_type, signal_name, msgid)
        content.append(field_get)
        content.append(field_set)
    return content


def generate_header(input_json_filename, json_dict):
    output = []

    header_top, header_bottom = gen_include_guard_class_decl_ctor(
        input_json_filename)
    output += header_top

    # fill in with more code...
    output += generate_get_set_functions(json_dict)
    output.append('\n\tprivate:')
    output += generate_private_fields(json_dict)

    output += header_bottom  # output = output + header_bottom
    return output


def generate_setter_src(signal_name, signal_type, signal_length, signal_comment):

    buffer = f"\t/*\n\tset {signal_comment}\n\t\*/\n"
    buffer += f'\tstd::string set_{signal_name}({signal_type} newValue);'

    return buffer


def create_output_dir_src():
    # check if folder exist if not creates it
    output_directory_src = os.path.join('Output', 'src')
    if not os.path.exists(output_directory_src):
        os.makedirs(output_directory_src)


def generate_source(input_json_filename, json_dict):
    output = []
    class_name = f'CAN_{input_json_filename}'
    output.append(f'#include "{input_json_filename}.h"\n')
    output.append(f'{class_name}::{class_name}() \n{{')
    msgid = "MsgId"
    start = "start"
    Id = 100
    output.append(f'\tm_{start}{msgid} = {Id};')
    add_value = 2
    for signal in json_dict["signals"]:
        signal_name = signal["name"]
        output.append(
            f'\tm_{signal_name}Get{msgid} = m_{start}{msgid} + {add_value};')
        output.append(
            f'\tm_{signal_name}Set{msgid} = m_{start}{msgid} + {add_value} + 1;')
        add_value += 2
    output.append(f'}}\n')

    for signal in json_dict["signals"]:
        signal_name = signal["name"]
        signal_type = signal["type"]
        id = 'ID'
        std = "std::string"
        sstream = 'sstream'
        msgid = 'MsgId'
        get_function = f'{std} {class_name}::get_{signal_name}()\n{{\n\t{std}stream {sstream};\n\t{sstream} << "{{\\"{id}\\": " << m_{signal_name}Get{msgid}\n\t\t<< ", \\"length\\":0"\n\t\t<< ",  \\"value\\": \"\" ";\n\treturn {sstream}.str();\n}}\n'
        set_function = f'{std} {class_name}::set_{signal_name}({signal_type} newValue)\n{{\n\t{std}stream {sstream};\n\t{sstream} << "{{\\"{id}\\": " << m_{signal_name}Set{msgid}\n\t\t<< ", \\"length\\":10"\n\t\t<< ", \\"value\\": \\"" << newValue << "\\" }}";\n\treturn {sstream}.str();\n}}\n'
        output.append(get_function)
        output.append(set_function)

    return output


if __name__ == "__main__":
    input_filename = "signals.json"
    json_dict = {}
    with open(input_filename) as file_fd:
        json_raw_content = file_fd.read()
        json_dict = json.loads(json_raw_content)
    # print(json_dict)
    input_json_filename = input_filename.replace(".json", "")
    # print(input_json_filename)

    # Writing  content to the header
    header_content = generate_header(input_json_filename, json_dict)
    header_content = generate_private_fields(json_dict)
    create_output_header_directory()
    header_file_path = 'Output/include/can_messages'
    header_file = f"{header_file_path}/{input_json_filename}.h"
    header_content = generate_header(input_json_filename, json_dict)
    header_content = "\n".join(header_content)
    write_output(header_file, header_content)

    # Writing content to the source file
    source_content = generate_source(input_json_filename, json_dict)
    create_output_dir_src()
    source_file_path = 'Output/src'
    source_file = f"{source_file_path}/{input_json_filename}.cpp"
    source_content = generate_source(input_json_filename, json_dict)
    source_content = "\n".join(source_content)
    write_output(source_file, source_content)
