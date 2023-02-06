/**
 * @file main.cpp
 * @author Oliver Joisten (https://oliver-joisten.se/)
 * @brief  The main Components of The Assignment
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../File_IO/lib/include/File_IO.h"
#include "../../CAN_Messages/Output/include/can_messages/signals.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::string, int> commands;

struct Command
{
    int ID;
    int length;
    int value;
};

void writeJsonArray(std::ofstream &outputFile, const std::vector<Command> &commandsData)
{
    outputFile << "{" << std::endl;
    outputFile << "\t[" << std::endl;
    for (const Command &command : commandsData)
    {

        outputFile << "\t\t{\"ID\": 0x" << std::hex << command.ID << ", "
                   << "\"length\": " << command.length << ", "
                   << "\"value\": " << command.value << "}"
                   << ",\n";
    }
    outputFile << "\t]" << std::endl;
    outputFile << "\n}\n";
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Missing input file name." << std::endl;
        return 1;
    }

    std::string inputFileName(argv[1]);
    std::string jsonFileName = inputFileName.substr(0, inputFileName.find_last_of(".")) + ".json";

    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1;
    }

    int id = 0;
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (commands.find(line) == commands.end())
        {
            commands[line] = id++;
        }
    }
    inputFile.close();

    inputFile.open(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return 1;
    }

    std::vector<Command> commandsData;
    while (std::getline(inputFile, line))
    {
        Command command;
        command.ID = commands[line];
        if (line == "set volume")
        {
            command.length = 8;
            command.value = 100;
        }
        else
        {
            command.length = 0;
            command.value = 0;
        }
        commandsData.push_back(command);
    }
    inputFile.close();

    std::ofstream outputFile(jsonFileName);
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Unable to open the output file." << std::endl;
        return 1;
    }

    writeJsonArray(outputFile, commandsData);

    outputFile.close();

    return 0;
}
