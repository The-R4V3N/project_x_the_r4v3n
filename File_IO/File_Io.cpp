
#include "file_io.h"
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Error: missing file name argument" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    FileOps FileIO;

    // Get input from the user
    std::string line;
    std::cout << "Enter the string you want to write to the file: ";
    std::getline(std::cin, line);

    // Write once.
    FileIO.write(fileName, line, 1);

    // Write multiple lines.
    std::vector<std::string> messages = {"Hello", "I am a", "Software", "Developer"};
    // iterate through the messages vector and writing each element to the file individually
    for (auto message : messages)
        FileIO.write(fileName, message, 1);

    // Check if file exists
    if (!FileIO.fileExists(fileName))
    {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    // Read once.
    std::cout << "Read once: " << std::endl;
    std::cout << FileIO.read<std::string>(fileName, 1) << std::endl;

    // Read multiple lines.
    std::vector<std::string> myData = FileIO.read<std::vector<std::string>>(fileName, 0);
    std::cout << "Read multiple lines: " << std::endl;
    for (auto data : myData)
    {
        std::cout << data << '\n';
    }
    return 0;
}
