/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Cook.hpp"
#include "Pizza.hpp"
#include <ctime>
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
    std::clock_t start;
    std::unique_lock<std::mutex> lk(m_mutex);

    while (!cooked) {
        if (!areIngredientsMet(pizza)) {
            m_condIng.wait(lk);
            continue;
        }
        start = clock();
        while (clock() - start < pizza.m_cookingTime * m_mult * 1000);
        cooked = true;
    }
}

void Plazza::Cook::takeCommand()
{
    Plazza::Pizza pizza = menu[0];
    while (1) {
        if (m_commands.tryPop(pizza) != 0)
            cookPizza(pizza);
    }
}
