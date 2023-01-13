/**
 * @file main.h
 * @author Oliver Joisten (https://oliver-joisten.webhostingfree.io/)
 * @brief A customer really wants to have a component to work with files.
 *            And due to PoC, he is agreed to have for now a limitations to work with std::string type for now.
 *            The component should have the following functions:
 *                  read from a file a line of string.read from a file a container of strings.
 *                  write to a file a string, which contains exactly 1 line.
 *                  write to a file a container of strings.
 *
 *             To make our life a bit easier, we can choose what container for string to use ( std::list, std::vector, etc.).
 *             And a customer told us the rule:
 *                  There is only one command on the line.
 *                  The component should be implemented as a library but also have a dummy application, which is working as "echo" ( meaning, if an user called dummy App with a file,the app should call functions to read the file and call functions to write an output file with the same content).
 *                  The component should have UT for the functionality (so plan ahead the code structure to be able to mock specific functions  ).
 *                  The component should also have a component test written on Python.
 *                  The idea is to create a temporary file with predefined input, call a dummy app, compare thegenerated output file with predefined data.).

 * @version 0.1
 * @date 2023-01-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>

class Fileio
{
private:
    std::string filename;
    std::list<std::string> contents;

public:
    Fileio(std::string filename) : filename(filename) {}

    std::list<std::string> file_one_read()
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string line;
            while (getline(file, line))
            {
                contents.push_back(line);
            }
            file.close();
            return contents;
        }
        else
        {
            std::cerr << "Error: Unable to open file" << std::endl;
            return contents;
        }
    }

    std::string file_one_write(std::list<std::string> data)
    {
        std::ofstream file(filename);
        if (file.is_open())
        {
            for (std::string line : data)
            {
                file << line << std::endl;
            }
            file.close();
            return "File written successfully";
        }
        else
        {
            std::cerr << "Error: Unable to open file" << std::endl;
            return "Error: Unable to open file";
        }
    }
};

#endif /* FILE_IO_H */