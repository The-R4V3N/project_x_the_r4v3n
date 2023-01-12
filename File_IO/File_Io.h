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
#include <cstring>

class file
{
private:
    file(const file &) = delete;
    file operator=(const file &) = delete;

public:
    file() {}

#if debug
    std::string write_one_line(&file){};

    std::vector write_more_lines(&file){};

    std::string read_one_line(&file){};

    std::vector read_more_lines(&file){};
#endif

    ~file()
    {
    }
};

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
