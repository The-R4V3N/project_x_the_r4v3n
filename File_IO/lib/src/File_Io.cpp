
std::vector<std::string> FileOps::read(std::string fileName, size_t line)
{
    std::vector<std::string> items;
    std::ifstream file(fileName);
    std::string data;
    if (line == 0)
    {
        while (std::getline(file, data))
            items.push_back(data);
    }
    else
    {
        int i = 1;
        while (std::getline(file, data))
        {
            if (i == line)
                items.push_back(data);
            i++;
        }
    }
    return items;
}

void write(std::string fileName, std::string data, size_t nLines)
{
    std::ofstream file(fileName, std::ios::app);
    if (file.is_open())
    {
        for (size_t i = 0; i < nLines; i++)
        {
            file << data;
            if (i < nLines - 1)
                file << '\n';
        }

        file.close();
    }
    else
    {
        throw std::runtime_error("Error: Unable to open file " + fileName + " for writing.");
    }
}

bool fileExists(const std::string &name)
{
    std::ifstream f(name.c_str());
    return f.good();
}