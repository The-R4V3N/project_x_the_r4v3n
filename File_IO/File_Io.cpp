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
    std::vector<std::string> messages = {"0x1224", "0x1DBC", "0xFFCB", "0x32A1"};
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