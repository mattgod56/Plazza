/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <map>
#include <thread>

#include "Cook.hpp"
#include "Process.hpp"
#include "MessageQueue.hpp"
#include "SafeQueue.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(std::size_t nbrCook, double cookingMult, std::size_t refillCD, std::string name);
            ~Kitchen() = default;

            void ingredientsRefill(void);
            void dailyKitchenLife();
            Plazza::MessageQueue &getQueue(void){return m_queue;}
            Plazza::MessageQueue &getDeathQueue(void){return m_queue;}
        private:
            void checkAlive(void);
            bool receiveCommand(void);
            std::map<Plazza::PizzaIngredients, int> m_ingredients;
            std::size_t m_nbrCook;
            double m_cookingTimeMult;
            std::size_t m_refillCD;
            std::mutex m_mutex;
            Plazza::Process m_process;
            Plazza::MessageQueue m_queue;
            Plazza::MessageQueue m_deathqueue;
            std::vector<Cook> m_cooks;
            SafeQueue m_commands;
            std::vector<std::thread> m_threads;
            std::condition_variable m_condPizza;
            std::condition_variable m_condIng;
    };
}
