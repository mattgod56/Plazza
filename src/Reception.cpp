/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Exception.hpp"
#include "Kitchen.hpp"
#include "MessageQueue.hpp"
#include "Pizza.hpp"
#include "queue.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <sstream>
#include <thread>
#include <vector>

void Plazza::Reception::getCommands()
{
    std::string line;
    std::string command;
    std::thread thrd(&Reception::deleteKitchen, this);

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
    if (name == "status") {
        return statusCmd();
    }
    for (auto pizza: menu) {
        if (name == typeToString.at(pizza.m_type))
            return pizzaFound(iss, pizza);
    }
}

void Plazza::Reception::statusCmd(void)
{
    std::array<std::string, INGREDIENTS_NBR + 1> arr = {"Dough", "Tomato", "Gruyere","Ham","Mushroom","Steak","Eggplant","GoatCheese","ChiefLove", "NbrOfCommands"};
    try {
        for (std::size_t i = 0; i < m_kitchens.size(); i++) {
            Plazza::MessageQueue::Datapack data;
            data.replycode = Plazza::QUEUE_MESSAGES::STATUS;
            m_kitchens.at(i)->getQueue() << data;
            std::cout << "waiting for answer" << std::endl;
            while (static_cast<Plazza::QUEUE_MESSAGES>(data.replycode) != Plazza::QUEUE_MESSAGES::STATUS_RES) {
                try {
                    m_kitchens.at(i)->getSndQueue() >> data;
                } catch (Plazza::MessageQueueError &) {}
            }
            std::cout << std::endl << "Kitchen[" << i << "]:" << std::endl;
            for (int i = 0; i <= INGREDIENTS_NBR; i++) {
                std::cout << arr[i] << ": " << data.data[i] << std::endl;
            }
            std::cout << std::endl;
        }
    } catch (Plazza::MessageQueueError &e) {
        return;
    }
}

void Plazza::Reception::communicateToKitchen(Plazza::Pizza &pizza)
{
    std::vector<int> vec;
    int min = 0;
    int idx = 0;

    for (std::size_t i = 0; i < m_kitchens.size(); i++) {
        Plazza::MessageQueue::Datapack data;
        for (int i = 0; i < QUEUE_DATA_SIZE; i++)
            data.data[i] = 0;
        data.replycode = Plazza::QUEUE_MESSAGES::INFO;
        try {
            m_kitchens.at(i)->getQueue() << data;
        }catch (Plazza::MessageQueueError &e) {
            std::cerr << e.what() << std::endl;
        }
        Plazza::MessageQueue::Datapack resdata;
        resdata.replycode = -1;
        while (static_cast<Plazza::QUEUE_MESSAGES>(resdata.replycode) != Plazza::QUEUE_MESSAGES::INFO_RES) {
            try {
                m_kitchens.at(i)->getSndQueue() >> resdata;
            } catch (Plazza::MessageQueueError &) {}
        }
        vec.push_back(resdata.data[0]);
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
    data.replycode = Plazza::QUEUE_MESSAGES::PIZZA;
    int pizidx = 0;
    for (int i = 1; i < 8; i *=2) {
        if (static_cast<Plazza::PizzaType>(i) == pizza.m_type)
            break;
        pizidx++;
    }
    for (int i = 0; i < QUEUE_DATA_SIZE; i++)
        data.data[i] = pizidx;
    m_kitchens.at(idx)->getQueue() << data;
}

void Plazza::Reception::createKitchen(Plazza::Pizza &pizza)
{
    std::cout << "creating new Kitchen" << std::endl;
    m_kitchens.push_back(
        std::make_unique<Plazza::Kitchen>(
        m_cookPerKitchen, m_cookingTimeMult, m_ingredientReplacementCD, QUEUE_NAME + std::to_string(m_ctr)));
    m_ctr++;
    int idx = 0;
    for (int i = 1; i < 8; i *=2) {
        if (static_cast<Plazza::PizzaType>(i) == pizza.m_type)
            break;
        idx++;
    }
    Plazza::MessageQueue::Datapack data;
    data.replycode = Plazza::QUEUE_MESSAGES::PIZZA;
    for (int i = 0; i < QUEUE_DATA_SIZE; i++)
        data.data[i] = idx;
    m_kitchens.back()->getQueue() << data;
}

void Plazza::Reception::deleteKitchen(void)
{
    while (true) {
        if (m_kitchens.size() > 0) {
            for (auto i = m_kitchens.begin(); i != m_kitchens.end(); i++) {
                Plazza::MessageQueue::Datapack data;
                data.replycode = 0;
                try {
                    i->get()->getDeathQueue() >> data;
                } catch (Plazza::MessageQueueError &e) {}
                if (data.replycode == Plazza::QUEUE_MESSAGES::DEAD) {
                    std::cout << "deleting kitchen" << std::endl;
                    m_kitchens.erase(i);
                    break;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}
