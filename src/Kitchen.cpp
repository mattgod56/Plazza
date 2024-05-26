/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "Exception.hpp"
#include "define.hpp"

#include <array>
#include <iostream>

Plazza::Kitchen::Kitchen(
    std::size_t nbrCook,
    double cookingMult,
    std::size_t refillCD,
    std::string name) : m_nbrCook(nbrCook), m_cookingTimeMult(cookingMult), m_refillCD(refillCD),
        m_queue(name, QUEUE_SIZE, QUEUE_MSG_SIZE), m_deathqueue(name + "_death", QUEUE_SIZE, QUEUE_MSG_SIZE)
{
    for (int i = PizzaIngredients::Dough; i != PizzaIngredients::NONE; i++)
        m_ingredients[static_cast<PizzaIngredients>(i)] = 5;
    m_process.startProcess();
    for (int i = 0; m_process.getPid() == 0 && i < (int)nbrCook; i++) {
        m_cooks.push_back(Cook(m_mutex, m_condIng, m_ingredients, m_commands, m_cookingTimeMult, m_occupiedCooks));
        m_threads.push_back(std::thread(&Cook::takeCommand, m_cooks.back()));
    }

    if (m_process.getPid() == 0)
        dailyKitchenLife();
}

void Plazza::Kitchen::ingredientsRefill(void)
{
    for (int i = PizzaIngredients::Dough; i != PizzaIngredients::NONE; i++) {
        m_ingredients[static_cast<PizzaIngredients>(i)] += 1;
    }
}

bool Plazza::Kitchen::receiveCommand(void)
{
    try {
        Plazza::MessageQueue::Datapack res;
        std::cout << "trying to get data" << std::endl;
        m_queue >> res;
        if (res.replycode == Plazza::QUEUE_MESSAGES::INFO) {
            Plazza::MessageQueue::Datapack send;
            send.replycode = Plazza::QUEUE_MESSAGES::INFO_RES;
            send.data[0] = 1;
            m_queue << send;
            return false;
        }

        if (res.replycode == Plazza::QUEUE_MESSAGES::PIZZA) {
            Plazza::Pizza pizza = menu[res.data[0]];
            m_commands.push(pizza);
            return true;
        }
        return false;
    } catch (Plazza::MessageQueueError &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

void Plazza::Kitchen::dailyKitchenLife(void)
{
    auto start = std::clock();
    auto ingredientClock = std::clock();
    while (std::clock() - start <= TIME_TO_CLOSE) {
        if (receiveCommand()) {
            start = std::clock();
        }
        if (std::clock() - ingredientClock > static_cast<long int>(m_refillCD * 1000)) {
            ingredientsRefill();
            m_condIng.notify_all();
            ingredientClock = std::clock();
        }
    }
    std::cout << "removing kitchen" << std::endl;
    std::array<int, QUEUE_DATA_SIZE>arr = {0};
    m_deathqueue.sendMessage(Plazza::QUEUE_MESSAGES::DEAD, arr);
    m_process.stopProcess();
}
