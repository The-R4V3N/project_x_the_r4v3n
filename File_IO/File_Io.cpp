#include "file_io.h"
#include <iostream>

int main(void)
{
    Fileio myfile("example.txt");

    std::list<std::string> contents = myfile.file_one_read();

    for (auto s : contents)
        std::cout << s << std::endl;

    std::string status = myfile.file_one_write(contents);

    std::cout << status << std::endl;

    return 0;
}