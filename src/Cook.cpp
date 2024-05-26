/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Cook.hpp"
#include "Pizza.hpp"
#include <chrono>
#include <iostream>
#include <mutex>

bool Plazza::Cook::areIngredientsMet(Pizza &pizza)
{
    for (auto iter = pizza.m_ingredients.begin(); iter != pizza.m_ingredients.end(); iter++) {
        if (m_ingredients[iter->first] < iter->second)
            return false;
    }
    for (auto iter = pizza.m_ingredients.begin(); iter != pizza.m_ingredients.end(); iter++)
        m_ingredients[iter->first] -= iter->second;
    return true;
}

void Plazza::Cook::cookPizza(Pizza &pizza)
{
    bool cooked = false;
    std::unique_lock<std::mutex> lk(m_mutex);
    std::cout << "entering" << std::endl;

    while (!cooked) {
        if (!areIngredientsMet(pizza)) {
            m_condIng.wait(lk);
            continue;
        }
        auto start = std::chrono::system_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count()
            < pizza.m_cookingTime * m_mult * 1000);
        cooked = true;
    }
    std::cout << "i cooked the " <<  typeToString.at(pizza.m_type)  << std::endl;
    m_occupiedCook -= 1;
}

void Plazza::Cook::takeCommand()
{
    dprintf(1, "enter cook\n");
    Plazza::Pizza pizza = menu[0];
    while (1) {
        if (m_commands.tryPop(pizza) != 0) {
            m_occupiedCook += 1;
            cookPizza(pizza);
        }
    }
}
