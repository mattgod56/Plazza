/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IPizza
*/

#pragma once
#include <vector>

namespace Plazza {

    enum Ingredients {
        DOUGH,
        TOMATO,
        GRUYERE,
        HAM,
        MUSHROOM,
        STEAK,
        GOAT_CHEESE,
        EGGPLANT,
        CHIEF_LOVE
    };

    class IPizza {
        public:
            virtual void cook() = 0;
    };

    class APizza: public IPizza {
        public:
        protected:
            double m_cookingTime;
            std::vector<Ingredients> m_ingredients;
    };
}
