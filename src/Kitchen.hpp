/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <map>
#include "IPizza.hpp"

namespace Plazza {
    class Kitchen {
        public:
            Kitchen();
            ~Kitchen() = default;
        private:
            std::map<Ingredients, int> m_ingredients;
            std::size_t m_pid; // change to process class
            // clock class
            // cook vector
    };
}
