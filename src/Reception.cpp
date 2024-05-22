/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Kitchen.hpp"
#include "Pizza.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

void Plazza::Reception::getCommands()
{
    std::string line;
    std::string command;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        while (std::getline(iss, command, ';'))
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
        communicateToKitchen(pizza);
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

void Plazza::Reception::communicateToKitchen(Plazza::Pizza &pizza)
{
    for (int i = 0; i < m_kitchens.size(); i++) {
        Plazza::MessageQueue &queue = m_kitchens.at(i)->getQueue();
        queue.sendMessage(pizza, sizeof(pizza));
        std::string res = queue.receiveMessage<std::string>();
        return;
    }
    createKitchen(pizza);
}

void Plazza::Reception::createKitchen(Plazza::Pizza &pizza)
{
    std::map<Plazza::PizzaIngredients, int>ingredients;

    for (int i = Plazza::Dough; i < Plazza::NONE; i++)
        ingredients[(static_cast<Plazza::PizzaIngredients>(i))] = 5;
    m_kitchens.push_back(
        std::make_unique<Plazza::Kitchen>(
        ingredients, QUEUE_NAME + std::to_string(m_kitchens.size())));
    m_kitchens.back()->assignCommand(pizza);
}
