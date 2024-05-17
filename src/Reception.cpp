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
    std::string command;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        while (getline(iss, command, ';'))
            checkCommand(command);
    }
}

void Plazza::Reception::pizzaFound(std::istringstream &iss, Pizza &pizza)
{
    std::string size;
    if (!getline(iss, size, ' '))
        return;
    std::cout << typeToString.at(pizza.m_type) << " " << size << std::endl;
}

void Plazza::Reception::checkCommand(std::string command)
{
    while (command[0] == ' ')
        command.erase(0, 1);
    std::cout << "line: " << command << std::endl;
    std::istringstream iss(command);
    std::string name;
    if (!getline(iss, name, ' '))
        return;
    for (auto pizza: menu) {
        if (name == typeToString.at(pizza.m_type))
            return pizzaFound(iss, pizza);
    }
}

void Plazza::Reception::createKitchen()
{

}
