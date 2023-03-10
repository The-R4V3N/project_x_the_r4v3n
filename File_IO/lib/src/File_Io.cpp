#include "File_IO.h"

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
    else
    {
        throw std::runtime_error("Error opening file " + fileName);
    }

    return data;
}

void FileOps::write(std::string fileName, std::vector<std::string> data)
{
    std::ofstream outFile(fileName, std::ios_base::app);
    if (outFile.is_open())
    {
        for (const std::string &line : data)
        {
            outFile << line << std::endl;
        }
        outFile.close();
    }
    else
    {
        throw std::runtime_error("Error opening file " + fileName + " for writing");
    }
}
