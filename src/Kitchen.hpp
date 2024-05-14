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

namespace Plazza {
    class Kitchen {
        public:
            Kitchen(std::map<std::string, int> &map) : m_ingredients(map) {}
            ~Kitchen() = default;

            void assignCommand(Pizza &);
            void ingredientsRefill(void);
        private:
            void checkAlive(void);
            std::map<std::string, int> &m_ingredients;
            std::mutex m_mutex;
            std::size_t m_pid; // change to process class
            // clock class
            // cook vector
    };
}
