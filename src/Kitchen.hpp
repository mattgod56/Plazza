/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <ctime>
#include <map>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <ctime>
#include <thread>

#include "Cook.hpp"
#include "Pizza.hpp"
#include "SafeQueue.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(std::size_t nbrCook, double cookingMult, std::size_t refillCD);
            ~Kitchen() = default;

            void ingredientsRefill(void);
            void dailyKitchenLife();
        private:
            void checkAlive(void);
            std::map<PizzaIngredients, int> m_ingredients;
            std::mutex m_mutex;
            std::vector<Cook> m_cooks;
            SafeQueue m_commands;
            std::vector<std::thread> m_threads;
            std::condition_variable m_condPizza;
            std::condition_variable m_condIng;
            double m_cookingTimeMult;
            std::size_t m_nbrCook;
            std::size_t m_refillCD;
    };
}
