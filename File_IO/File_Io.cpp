#include "file_io.h"
#include <string>
#define FILE "CAN_file.txt"

int main(void)
{

    FileIo FileIO;
    std::fstream dataFile;
    // Write once.
    FileIO.writeLine(FILE);
    // Write multiple lines.
    std::vector<std::string> messages = {"Hello", "I am a", "Software", "Developer"};
    FileIO.writeLines(FILE, messages);
    // Read once.
    std::cout << "Read once: " << std::endl;
    std::cout << FileIO.readLine(dataFile, FILE) << std::endl;
    // Read multiple lines.
    std::vector<std::string> myData = FileIO.readLines(dataFile, FILE);
    std::cout << "Read multiple lines: " << std::endl;
    for (auto data : myData)
    {
        std::cout << data << '\n';
    }
}