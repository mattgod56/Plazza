/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <map>
#include <mutex>
#include <string>

#include "Pizza.hpp"
#include "Process.hpp"
#include "MessageQueue.hpp"
#include "define.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(std::map<Plazza::PizzaIngredients, int> &map, std::string name) : m_ingredients(map), m_queue(name, QUEUE_SIZE, QUEUE_MSG_SIZE)
            {
                waitForCommand();
            }
            ~Kitchen() = default;

            void waitForCommand(void);
            void assignCommand(Pizza &);
            void ingredientsRefill(void);
            Plazza::MessageQueue &getQueue(void){return m_queue;}
        private:
            void checkAlive(void);
            std::map<Plazza::PizzaIngredients, int> &m_ingredients;
            std::mutex m_mutex;
            Plazza::Process m_process;
            Plazza::MessageQueue m_queue;
    };
}
