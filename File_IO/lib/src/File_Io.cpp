#include "File_Io.h"

std::vector<std::string> FileOps::read(std::string fileName, size_t line)
{
    std::vector<std::string> data;
    std::ifstream inFile(fileName);
    std::string lineData;
    if (inFile.is_open())
    {
        if (line)
        {
            for (size_t i = 0; i < line; i++)
            {
                if (std::getline(inFile, lineData))
                {
                    data.push_back(lineData);
                }
            }
        }
        else
        {
            while (std::getline(inFile, lineData))
            {
                data.push_back(lineData);
            }
        }
        inFile.close();
    }
    return data;
}

void FileOps::write(std::string fileName, std::string data, size_t nLines)
{
    std::ofstream outFile(fileName, std::ios_base::app);
    if (outFile.is_open())
    {
        if (nLines)
        {
            for (size_t i = 0; i < nLines; i++)
            {
                outFile << data << std::endl;
            }
        }
        else
        {
            outFile << data;
        }
        outFile.close();
    }
}

bool FileOps::fileExists(const std::string &name)
{
    std::ifstream f(name.c_str());
    return f.good();
}
