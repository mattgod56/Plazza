/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include <iostream>
#include <sstream>

void Plazza::Reception::getCommands()
{
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        checkCommand(line);
    }
}

void Plazza::Reception::checkCommand(std::string str)
{

}

void Plazza::Reception::createKitchen()
{

}
