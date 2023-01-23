#include "File_Io.h"

bool FileOps::fileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

std::vector<std::string> FileOps::read(std::string fileName)
{
    std::vector<std::string> data;
    std::string line;
    std::ifstream inFile(fileName);
    if (inFile.is_open())
    {
        while (std::getline(inFile, line))
        {
            data.push_back(line);
        }
        inFile.close();
    }
    return data;
}

void FileOps::write(std::string fileName, std::string data)
{
    std::ofstream outFile(fileName, std::ios_base::app);
    if (outFile.is_open())
    {
        outFile << data << std::endl;
        outFile.close();
    }
}
