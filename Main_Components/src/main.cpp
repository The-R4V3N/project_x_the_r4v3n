#include "../../File_IO/lib/include/File_IO.h"
#include "../../CAN_Messages/Output/include/can_messages/signals.h"
#include <iostream>
#include <iterator>

std::string parse_get_func_and_call(std::string line)
{
    const std::string get_keyword("get");
    std::string result;
    size_t pos_of_get = line.find(get_keyword);
    // position of get + the length of the "get" + extra whitespace
    size_t pos_start_signal_name = pos_of_get + get_keyword.size() + 1;
    size_t pos_of_separator = line.find(" ", pos_start_signal_name);
    std::string get_signal_name = line.substr(pos_start_signal_name, pos_of_separator - pos_start_signal_name);

    // ignore space before
    std::string value = line.substr(pos_of_separator + 1,
                                    // from total length (position of first element + last element)
                                    line.length() - ((pos_of_separator + 1) + 1));

    std::cout << "signal_name  = |" << get_signal_name
              << "| value |"
              << value << "|" << std::endl;

    if (get_signal_name.compare("temperature") == 0)
    {
        CAN_signals signal_obj;
        return signal_obj.get_temperature();
    }
    else if (get_signal_name.compare("humidity") == 0)
    {
        CAN_signals signal_obj;
        return signal_obj.get_humidity();
    }
    // else
    // if (signal_name.compare("stop_signal_light") == 0)
    // {
    //     signal_obj.get_stop_signal_light();
    // }
    // else
    // if (signal_name.compare("temperature") == 0)

    return result;
}

std::string parse_set_func_and_call(std::string line)
{
    const std::string set_keyword("set");
    std::string result;
    size_t pos_of_set = line.find(set_keyword);
    // positioin of set + the lenght of the "Set" + extra whitespace
    size_t pos_start_signal_name = pos_of_set + set_keyword.size() + 1;
    size_t pos_of_separator = line.find(" ", pos_start_signal_name);
    std::string set_signal_name = line.substr(pos_start_signal_name, pos_of_separator - pos_start_signal_name);
    // ignore space before
    std::string value = line.substr(pos_of_separator + 1,
                                    // from total length (position of first element + last element)
                                    line.length() - ((pos_of_separator + 1) + 1));

    std::cout << "signal_name  = |" << set_signal_name
              << "| value |"
              << value << "|" << std::endl;

    if (set_signal_name.compare("temperature") == 0)
    {
        float f_value = std::stof(value);
        CAN_signals signal_obj;
        return signal_obj.set_temperature(f_value);
    }
    else if (set_signal_name.compare("humidity") == 0)
    {
        uint8_t u_value = std::stoul(value) & 0xFF;
        CAN_signals signal_obj;
        return signal_obj.set_humidity(u_value);
    }
    // else
    // if (signal_name.compare("stop_signal_light") == 0)
    // {
    //     bool b_value = false;
    //     if (value.compare("enabled") == 0)

    //     {
    //         b_value = true;

    //     }
    //     CAN_signals signal_obj;
    //     return signal_obj.set_stop_signal_light(b_value);
    //     }
    // else
    // if (signal_name.compare("temperature") == 0)
    return result;
}

/* convert list of comands into json file generated class from Can_Messages*/
std::vector<std::string> convert(std::vector<std::string> raw_input)
{

    std::vector<std::string> output;

    // for c++ 11 and later standards

    for (std::string &line : raw_input)
    {
        size_t pos_of_get = line.find("get");
        if (pos_of_get != std::string::npos && pos_of_get < 2)
        {
            std::string out = parse_get_func_and_call(line);
            output.push_back(out);
            // call a function to parse get lines
        }

        size_t pos_of_set = line.find("set");
        if (pos_of_set != std::string::npos && pos_of_set < 2)
        {

            std::string out = parse_set_func_and_call(line);
            output.push_back(out);
            // call a function to parse set lines
        }
    }

    return output;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "sorry you should call"
                  << std::endl
                  << argv[0] << " input_file output_file" << std::endl;
        return 1;
    }

    std::string input_filename(argv[1]);
    std::string output_filename(argv[2]);

    FileOps input;
    std::vector<std::string> input_content = input.read(input_filename);

    // define a container for result
    std::vector<std::string> output_content = convert(input_content);

    // Decoration part
    std::vector<std::string> final_output = {"{", "\t["};

    auto lineIt = output_content.begin();
    for (;
         std::next(lineIt) != output_content.end();
         ++lineIt)
    {
        final_output.push_back((*lineIt) + ";");
    }
    final_output.push_back(*lineIt);

    // closing json Document
    final_output.emplace_back("\t]");
    final_output.emplace_back("}");

    FileOps output;
    output.write(output_filename, final_output);

    return 0;
}
/*
./ Main_Components / main_component../ Main_Components / output / signals.txt./ output.txt
*/