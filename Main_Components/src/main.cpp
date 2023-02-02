
/**
 * @file main.cpp
 * @author Oliver Joisten (https://oliver-joisten.se/)
 * @brief  The main Components of The Assignment
 * @version 0.1
 * @date 2023-01-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "File_Io.h"
#include <can_messages/signals.h>
#include <iostream>

int main(int argc, char *argv[])
{
    CAN_signals Signals;

    File_Io myFile("test");
    std::cout << "it is kind of opened" << std::endl;
    return 0;
}