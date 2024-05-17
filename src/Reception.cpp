/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Pizza.hpp"
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
    std::string strAmount;
    if (!getline(iss, strAmount, ' '))
        return;
    if (!(strAmount.at(0) == 'x'))
        return;
    strAmount.erase(0, 1);
    std::size_t idx = 0;
    int amount = std::stoi(strAmount, &idx);
    if (idx != strAmount.size() || !(amount > 0))
        return;
    for (int i = 0; i < amount; i++) {
        std::cout << "One " << size << " " << typeToString.at(pizza.m_type) << " please !" << std::endl;
    }
}

void Plazza::Reception::checkCommand(std::string command)
{
    while (command[0] == ' ')
        command.erase(0, 1);
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
