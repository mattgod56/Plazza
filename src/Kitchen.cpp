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
    dprintf(1, "tactical refill\n");
    for (int i = PizzaIngredients::Dough; i != PizzaIngredients::NONE; i++) {
        m_ingredients[static_cast<PizzaIngredients>(i)] += 1;
    }
}

bool Plazza::Kitchen::receiveCommand(void)
{
    try {
        Plazza::MessageQueue::Datapack res;
        // std::cout << "tryying to get data" << std::endl;
        // dprintf(1, "trying to read\n");
        m_queue >> res;
        dprintf(1, "command read\n");
        if (res.replycode == Plazza::QUEUE_MESSAGES::INFO) {
            Plazza::MessageQueue::Datapack send;
            send.replycode = Plazza::QUEUE_MESSAGES::INFO_RES;
            send.data[0] = m_commands.length();
            m_queue << send;
            return false;
        }

        if (res.replycode == Plazza::QUEUE_MESSAGES::PIZZA) {
            dprintf(1, "command info recognized\n");
            Plazza::Pizza pizza = menu[res.data[0]];
            m_commands.push(pizza);
            return true;
        }
        return false;
    } catch (Plazza::MessageQueueError &e) {
        // std::cerr << e.what() << std::endl;

        return false;
    }
}

void Plazza::Kitchen::dailyKitchenLife(void)
{
    auto start = std::chrono::system_clock::now();
    auto ingredientClock = std::chrono::system_clock::now();
    auto duration = std::chrono::system_clock::now() - start;
    auto durationIngredient = std::chrono::system_clock::now() - ingredientClock;
    while (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() <= TIME_TO_CLOSE) {
        // dprintf(1, "Time: %ld\n", std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
        if (receiveCommand() || m_occupiedCooks > 0 || m_commands.length() > 0) {
            // dprintf(1, "received command\n");
            start = std::chrono::system_clock::now();
        }
        if (std::chrono::duration_cast<std::chrono::milliseconds>(durationIngredient).count()
            > static_cast<long int>(m_refillCD)) {
            ingredientsRefill();
            m_condIng.notify_all();
            ingredientClock = std::chrono::system_clock::now();
        }
        duration = std::chrono::system_clock::now() - start;
        durationIngredient = std::chrono::system_clock::now() - ingredientClock;
        // dprintf(1, "TIME %ld %d %d\n",duration.count(), m_commands.length(), m_occupiedCooks);
    }
    dprintf(1, "removing kitchen\n");
    std::array<int, QUEUE_DATA_SIZE>arr;
    arr[0] = 0;
    m_deathqueue.sendMessage(Plazza::QUEUE_MESSAGES::DEAD, arr);
    dprintf(1, "I sent death\n");
    m_process.stopProcess();
}
