
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
    FileIo FileIO;
    std::fstream dataFile;
    // Get input from the user
    std::string line;
    std::cout << "Enter the string you want to write to the file: ";
    std::getline(std::cin, line);

    // Write once.
    FileIO.writeLine(fileName, line);

    // Write multiple lines.
    std::vector<std::string> messages = {"Hello", "I am a", "Software", "Developer"};
    FileIO.writeLines(fileName, messages);

    // Read once.
    std::cout << "Read once: " << std::endl;
    std::cout << FileIO.readLine(dataFile, fileName) << std::endl;

    // Read multiple lines.
    std::vector<std::string> myData = FileIO.readLines(dataFile, fileName);
    std::cout << "Read multiple lines: " << std::endl;
    for (auto data : myData)
    {
        std::cout << data << '\n';
    }
}
