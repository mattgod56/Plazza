/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <mutex>
#include <condition_variable>

#include "Pizza.hpp"
#include "SafeQueue.hpp"

namespace Plazza
{
    class Cook {
        public:
            Cook(std::mutex &mutex, std::condition_variable &condIng,
                std::map<PizzaIngredients, int> &ingredients, SafeQueue &commands, double &mult, int &occupiedCook) :
                m_mutex(mutex), m_condIng(condIng), m_ingredients(ingredients), m_commands(commands), m_mult(mult), m_occupiedCook(occupiedCook) { }
            ~Cook() = default;

            void takeCommand();
            void cookPizza(Pizza &pizza);
            bool areIngredientsMet(Pizza &pizza);
        private:
            std::mutex &m_mutex;
            std::condition_variable &m_condIng;
            std::map<PizzaIngredients, int> &m_ingredients;
            SafeQueue &m_commands;
            double &m_mult;
            int &m_occupiedCook;
    };
}
