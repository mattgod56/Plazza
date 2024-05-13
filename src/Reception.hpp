/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#pragma once

#include <string>

namespace Plazza {

    class Reception {
        public:
            Reception(double cookingTimeMult, int cookPerKitchen, std::size_t replacementCD):
                m_cookingTimeMult(cookingTimeMult),
                m_cookPerKitchen(cookPerKitchen),
                m_ingredientReplacementCD(replacementCD) {}
            ~Reception() = default;

            void loop();

        private:
            double m_cookingTimeMult;
            int m_cookPerKitchen;
            std::size_t m_ingredientReplacementCD;
    };
}
