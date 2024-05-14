/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <array>
#include <mutex>
#include <memory>

#include "Pizza.hpp"

namespace Plazza
{
    class Cook {
        public:
            Cook(std::mutex &mutex) : m_mutex(mutex) {}
            ~Cook();

            void cookPizza(std::map<std::string, int> &);
        private:
            std::array<std::unique_ptr<Plazza::Pizza>, 2> m_commands;
            std::mutex &m_mutex;
    };
}