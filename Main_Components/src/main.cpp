#include "../../File_IO/lib/include/File_IO.h"
#include "../../CAN_Messages/Output/include/can_messages/signals.h"
#include <iostream>
#include <iterator>

// #define PRINT_DEBUG_LINE_INFO  std::cout << __FUNCTION__ << ":" << __LINE__ << std::endl;

std::string parse_get_func_and_call(std::string line)
{
    const std::string get_keyword("get");
    std::string result;
    size_t pos_of_get = line.find(get_keyword);

    // Check if the "get" keyword is found
    if (pos_of_get == std::string::npos)
    {
        std::cerr << "Error: Could not find get keyword in line: " << line << std::endl;
        return result;
    }

    // position of get+ the length of the "set" + extra whitespace
    size_t pos_start_signal_name = pos_of_get + get_keyword.size() + 1;
    // size_t pos_of_separator = line.find(" ", pos_start_signal_name);

    // Check if the signal name was extracted correctly
    if (line.length() == std::string::npos)
    {
        std::cerr << "Error: Could not find separator in line: " << line << std::endl;
        return result;
    }

    std::string get_signal_name = line.substr(pos_start_signal_name, line.length() - (pos_start_signal_name + 1));

    bool shall_we_delete = line[line.size() - 1] == '\r';
    // ignore space before
    // std::string value = line.substr(pos_of_separator + 1,
    //                                 // from total length (position of first element + last element)
    //                                 line.length() - ((pos_of_separator + 1) + (shall_we_delete ? 1 : 0)));

    std::cout << "signal_name  = |" << get_signal_name
              << "| value |"
              //<< value
              << " |"
              << std::endl;

    if (get_signal_name.compare("temperature") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_temperature();
    }
    else if (get_signal_name.compare("humidity") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_humidity();
    }
    else if (get_signal_name.compare("front_sensor_status") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_front_sensor_status();
    }
    else if (get_signal_name.compare("flow_rate") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_flow_rate();
    }
    else if (get_signal_name.compare("flow_meter_sensor_status") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_flow_meter_sensor_status();
    }
    else if (get_signal_name.compare("light_intensity") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_light_intensity();
    }
    else if (get_signal_name.compare("light_intensity_sensor_status") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_light_intensity_sensor_status();
    }
    else if (get_signal_name.compare("water_level") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_water_level();
    }
    else if (get_signal_name.compare("water_level_sensor_status") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_water_level_sensor_status();
    }
    else if (get_signal_name.compare("soil_moisture") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_soil_moisture_sensor_status();
    }
    else if (get_signal_name.compare("soil_moisture_sensor_status") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_soil_moisture_sensor_status();
    }
    else if (get_signal_name.compare("stop_signal_light") == 0)
    {
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.get_stop_signal_light();
    }
    else
    {
        std::cerr << "Error: Could not extract expected signal name from line: " << line << std::endl;
    }

    return result;
}

std::string parse_set_func_and_call(std::string line)
{
    const std::string set_keyword("set");
    std::string result;
    size_t pos_of_set = line.find(set_keyword);

    // Check if the "set" keyword is found
    if (pos_of_set == std::string::npos)
    {
        std::cerr << "Error: \"set\" keyword not found in input string." << std::endl;
        return result;
    }

    // position of set + the lenght of the "Set" + extra whitespace
    size_t pos_start_signal_name = pos_of_set + set_keyword.size() + 1;
    size_t pos_of_separator = line.find(" ", pos_start_signal_name);

    // Check if the signal name was extracted correctly
    if (pos_of_separator == std::string::npos)
    {
        std::cerr << "Error: Separator for signal name not found in input string." << std::endl;
        return result;
    }

    std::string set_signal_name = line.substr(pos_start_signal_name, pos_of_separator - pos_start_signal_name);

    bool shall_we_delete = line[line.size() - 1] == '\r';
    // ignore space before
    std::string value = line.substr(pos_of_separator + 1,
                                    // from total length (position of first element + last element)
                                    line.length() - ((pos_of_separator + 1) + (shall_we_delete ? 1 : 0)));

    std::cout << "signal_name  = |" << set_signal_name
              << "| value |"
              << value << "|" << std::endl;

    if (set_signal_name.compare("temperature") == 0)
    {
        float f_value;
        try
        {
            f_value = std::stof(value);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to float." << std::endl;
            return result;
        }

        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_temperature(f_value);
    }
    else if (set_signal_name.compare("humidity") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }

        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_humidity(u_value);
    }
    else if (set_signal_name.compare("front_sensor_status") == 0)
    {
        bool b_value = false;
        if (value.compare("enabled") == 0)
        {
            b_value = true;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_front_sensor_status(b_value);
    }
    else if (set_signal_name.compare("flow_rate") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_flow_rate(u_value);
    }
    else if (set_signal_name.compare("flow_meter_sensor_status") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_flow_meter_sensor_status(u_value);
    }
    else if (set_signal_name.compare("light_intensity") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_light_intensity(u_value);
    }
    else if (set_signal_name.compare("light_intensity_sensor_status") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_light_intensity_sensor_status(u_value);
    }
    else if (set_signal_name.compare("water_level") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_water_level(u_value);
    }
    else if (set_signal_name.compare("water_level_sensor_status") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_water_level_sensor_status(u_value);
    }
    else if (set_signal_name.compare("soil_moisture") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_soil_moisture(u_value);
    }
    else if (set_signal_name.compare("soil_moisture_sensor_status") == 0)
    {
        uint8_t u_value;
        try
        {
            u_value = std::stoul(value) & 0xFF;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Error: Could not convert value to unsigned integer." << std::endl;
            return result;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_soil_moisture_sensor_status(u_value);
    }
    else if (set_signal_name.compare("stop_signal_light") == 0)
    {
        bool b_value = false;
        if (value.compare("enabled") == 0)
        {
            b_value = true;
        }
        CAN_signals signal_obj;
        return "\t\t" + signal_obj.set_stop_signal_light(b_value);
    }
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
            // call a function to parse set lines
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
    std::vector<std::string> final_output = {"{", "\t \"cmds\" : ["};

    if (output_content.empty() != true)
    {
        auto lineIt = output_content.begin();
        for (;
             std::next(lineIt) != output_content.end();
             ++lineIt)
        {
            final_output.push_back((*lineIt) + ",");
        }

        final_output.push_back(*lineIt);
    }

    // closing json Document
    final_output.emplace_back("\t]");
    final_output.emplace_back("}");

    FileOps output;
    output.write(output_filename, final_output);

    return 0;
}
/*
Command to run after compiling
./Main_Components/main_component ../Main_Components/input/signals.txt ./output.json
*/