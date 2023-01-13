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
#include <fstream>
#include <vector>
#include <string>
#include <list>

class file
{
public:
    file(const std::string &fileName, const std::string &mode = "r") { open(fileName, mode); }
    ~file() { close(); }

    // delete copy constructor and copy assignment operator to prevent copying
    file(const file &) = delete;
    file operator=(const file &) = delete;

    // read a line of string from the file
    std::string readLine()
    {
        std::string line;
        std::getline(fileStream, line);
        return line;
    }

    // read a container of strings from the file
    std::vector<std::string> readLines()
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(fileStream, line))
        {
            lines.push_back(line);
        }
        return lines;
    }

    // write a string to the file, which contains exactly 1 line
    void writeLine(const std::string &line)
    {
        fileStream << line << std::endl;
    }

    // write a container of strings to the file
    void writeLines(const std::vector<std::string> &lines)
    {
        for (const auto &line : lines)
        {
            fileStream << line << std::endl;
        }
    }

private:
    std::fstream fileStream;

    void open(const std::string &fileName, const std::string &mode)
    {
        fileStream.open(fileName, std::ios::out | std::ios::in);
        if (!fileStream.is_open())
        {
            throw std::runtime_error("Failed to open file: " + fileName);
        }
    }

    void close()
    {
        if (fileStream.is_open())
        {
            fileStream.close();
        }
    }
};

#if debug
std::string write_one_line(&file){};

std::vector write_more_lines(&file){};

std::string read_one_line(&file){};

std::vector read_more_lines(&file){};
#endif

#endif /* FILE_IO_H */

/*
req1: we will use C++
req2: we are working with std::string type.
BigTask: write a C++ class to work with files.
- create header and source file for C++ class
- create an empty class.
- create a source file for main function and some tests.
- include neccessary header files
- define main function and create an object of a class for file File_IO
- ?build it and see at least some output

*/
