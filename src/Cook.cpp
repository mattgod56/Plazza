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

    dprintf(1, "I cooka da pizza\n");
    while (!cooked) {
        if (!areIngredientsMet(pizza)) {
            dprintf(1, "I'm blue\n");
            m_condIng.wait(lk);
            continue;
        }
        dprintf(1, "TIME TO COOK\n");
        start = clock();
        while (clock() - start < pizza.m_cookingTime * m_mult * 1000) { dprintf(1, "cooking process: %ld / %f\n", clock() - start, pizza.m_cookingTime * m_mult * 1000); }
        dprintf(1, "COOKING'S OVER\n");
        cooked = true;
    }
    dprintf(1, "One %s ready !\n", typeToString.at(pizza.m_type).c_str());
}

void Plazza::Cook::takeCommand()
{
    dprintf(1, "I wish to eat pizzas\n");
    Plazza::Pizza pizza = menu[0];
    dprintf(1, "Entering the shadow realm\n");
    while (1) {
        dprintf(1, "Shadow warrior in action\n");
        if (m_commands.tryPop(pizza) != 0)
            cookPizza(pizza);
    }
}
