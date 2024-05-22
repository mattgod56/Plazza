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
#include "Process.hpp"
#include "MessageQueue.hpp"
#include "define.hpp"
#include "SafeQueue.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(std::size_t nbrCook, double cookingMult, std::size_t refillCD)
            ~Kitchen() = default;

            void waitForCommand(void);
            void assignCommand(Pizza &);
            void ingredientsRefill(void);
            void dailyKitchenLife();
            Plazza::MessageQueue &getQueue(void){return m_queue;}
        private:
            void checkAlive(void);
            std::map<Plazza::PizzaIngredients, int> m_ingredients;
            std::mutex m_mutex;
            Plazza::Process m_process;
            Plazza::MessageQueue m_queue;
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
