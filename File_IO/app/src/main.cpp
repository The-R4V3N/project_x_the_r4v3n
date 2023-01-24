#include "File_Io.h"

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
    std::cout << "Enter the string you want to write to the file: " << std::endl;
    std::getline(std::cin, line);

    // Get input from the user
    std::vector<std::string> messages;
    std::string message;
    std::cout << "Enter the messages you want to write to the file: " << std::endl;
    int counter = 0;
    while (std::getline(std::cin, message))
    {
        if (message.empty() || counter == 5)
            break;
        messages.push_back(message);
        counter++;
    }

    // Write multiple lines.
    for (auto message : messages)
        FileIO.write(fileName, messages);

    // Check if file exists
    std::ifstream file(fileName);
    if (!file.good())
    {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    // Read once.
    std::cout << "Read once: " << std::endl;
    std::vector<std::string> readOnce = FileIO.read(fileName);
    if (!readOnce.empty())
        std::cout << readOnce[0] << std::endl;
    else
        std::cout << "Error: Unable to read from file" << std::endl;

    // Read multiple lines.
    std::vector<std::string> myData = FileIO.read(fileName);
    std::cout << "Read multiple lines: " << std::endl;
    for (auto data : myData)
    {
        std::cout << data << '\n';
    }
    return 0;
}
