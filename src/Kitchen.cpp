/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include <chrono>
#include <iostream>
#include <thread>
#include "Kitchen.hpp"
#include "Pizza.hpp"
#include "define.hpp"

Plazza::Kitchen::Kitchen(std::size_t nbrCook, double cookingMult, std::size_t refillCD, std::string name): m_nbrCook(nbrCook), m_cookingTimeMult(cookingMult), m_refillCD(refillCD),  m_queue(name, QUEUE_SIZE, QUEUE_MSG_SIZE)
{
    for (int i = 0; i < nbrCook; i++) {
        m_cooks.push_back(Cook(m_mutex, m_condIng, m_ingredients, m_commands, m_cookingTimeMult));
        m_threads.push_back(std::thread(&Cook::takeCommand, m_cooks.back()));
    }
    for (int i = PizzaIngredients::Dough; i != PizzaIngredients::End; i++)
        m_ingredients[static_cast<PizzaIngredients>(i)] = 5;
    m_process.startProcess();

    if (m_process.getPid() == 0)
        waitForCommand();
}

void Plazza::Kitchen::ingredientsRefill(void)
{
    for (int i = PizzaIngredients::Dough; i != PizzaIngredients::NONE; i++) {
        m_ingredients[static_cast<PizzaIngredients>(i)] += 1;
    }
}

void Plazza::Kitchen::waitForCommand(void)
{
    Plazza::Pizza piz;

    while (true) {
        piz = m_queue.receiveMessage<Plazza::Pizza>();
    }
}

void Plazza::Kitchen::dailyKitchenLife(void)
{
    auto start = std::clock();
    auto ingredientClock = std::clock();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    while (std::clock() - start <= TIME_TO_CLOSE) {
        if (/*RECEIVE COMMAND*/true) {
            start = std::clock(); //REFRESH START
            m_commands.push(menu[0]);
            m_condPizza.notify_one();
        }
        if (std::clock() - ingredientClock > m_refillCD * 1000) {
            ingredientsRefill();
            m_condIng.notify_all();
            ingredientClock = std::clock();
        }
    }
    std::cout << "MY KITCHEN NOOOOOOOOOOOO" << std::endl; // should stop this process
}
