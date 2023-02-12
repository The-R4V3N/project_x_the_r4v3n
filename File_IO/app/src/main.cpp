#include "File_IO.h"

int main(int argc, char *argv[])
{
    // Check if the file name argument is present
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

    // Get message from the user
    std::vector<std::string> messages;
    std::string message;
    std::cout << "Enter up to 5 messages you want to write to the file. Push ENTER to brake out: " << std::endl;
    int counter = 0;
    while (std::getline(std::cin, message))
    {
        if (message.empty() || counter == 5)
            break;
        messages.push_back(message);
        counter++;
    }

    // Write message to the file.

    FileIO.write(fileName, messages);

    // Check if file exists
    std::ifstream file(fileName);
    if (!file.good())
    {
        std::cout << "File not found!" << std::endl;
        return 1;
    }

    // Read and print the first line
    std::vector<std::string> readOnce = FileIO.read(fileName);
    if (!readOnce.empty())
    {
        std::cout << "Read once: " << std::endl;
        std::cout << readOnce[0] << std::endl;
    }
    else
    {
        std::cout << "Error: Unable to read from file" << std::endl;
    }

    // Read and print all lines
    std::vector<std::string> myData = FileIO.read(fileName);
    if (!myData.empty())
    {
        std::cout << "Read multiple lines: " << std::endl;
        for (const auto &data : myData)
        {
            std::cout << data << '\n';
        }
    }
    else
    {
        std::cout << "Error: Unable to read from file" << std::endl;
    }
    return 0;
}
