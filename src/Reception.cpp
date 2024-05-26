/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "MessageQueue.hpp"
#include "queue.hpp"

#include <array>
#include <exception>
#include <iostream>
#include <sstream>
#include <thread>

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
    std::vector<int> vec;
    int min = 0;
    int idx = 0;

    for (std::size_t i = 0; i < m_kitchens.size(); i++) {
        Plazza::MessageQueue &queue = m_kitchens.at(i)->getQueue();
        std::array<int, QUEUE_DATA_SIZE> arr = {0};
        try {
            queue.sendMessage(Plazza::QUEUE_MESSAGES::INFO, arr);
            Plazza::MessageQueue::Datapack data;
            queue >> data;
            vec.push_back(data.data[0]);
        }catch (std::exception &e) {

        }
    }
    if (m_kitchens.size() > 0) {
        min = vec[0];
        for (std::size_t i = 0; i < vec.size(); i++) {
            if (vec[i] < min) {
                min = vec[i];
                idx = i;
            }
        }
    }
    if (min >= m_cookPerKitchen * 2 || m_kitchens.size() == 0)
        return createKitchen(pizza);
    Plazza::MessageQueue::Datapack data;
    int pizidx = 0;
    for (int i = 1; i < 8; i *=2) {
        if (static_cast<Plazza::PizzaType>(i) == pizza.m_type)
            break;
        pizidx++;
    }
    data.replycode = Plazza::QUEUE_MESSAGES::PIZZA;
    data.data[0] = pizidx;
    m_kitchens.at(idx)->getQueue() << data;
}

void Plazza::Reception::createKitchen(Plazza::Pizza &pizza)
{
    //  << "creating new Kitchen" << std::endl;
    m_kitchens.push_back(
        std::make_unique<Plazza::Kitchen>(
        m_cookPerKitchen, m_cookingTimeMult, m_ingredientReplacementCD, QUEUE_NAME + std::to_string(m_kitchens.size())));
    int idx = 0;
    for (int i = 1; i < 8; i *=2) {
        if (static_cast<Plazza::PizzaType>(i) == pizza.m_type)
            break;
        idx++;
    }
    Plazza::MessageQueue::Datapack data;
    data.replycode = Plazza::QUEUE_MESSAGES::PIZZA;
    data.data[0] = idx;
    m_kitchens.back()->getQueue() << data;
}

void Plazza::Reception::deleteKitchen(void)
{
    while (true) {
        for (auto i = m_kitchens.begin(); i != m_kitchens.end(); i++) {
            Plazza::MessageQueue::Datapack data;
            i->get()->getDeathQueue() >> data;
            if (data.replycode == Plazza::QUEUE_MESSAGES::DEAD) {
                m_kitchens.erase(i);
                break;
            }
        }
    }
}
