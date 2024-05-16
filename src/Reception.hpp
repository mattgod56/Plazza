/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#pragma once

#include <string>
#include "IPizza.hpp"
#include "Kitchen.hpp"

namespace Plazza {

    class Reception {
        public:
            Reception(double cookingTimeMult, int cookPerKitchen, std::size_t replacementCD):
                m_cookingTimeMult(cookingTimeMult),
                m_cookPerKitchen(cookPerKitchen),
                m_ingredientReplacementCD(replacementCD) {}
            ~Reception() = default;

            void getCommands();
            void checkCommand(std::string str);
            void createKitchen();

        private:
            double m_cookingTimeMult;
            int m_cookPerKitchen;
            std::size_t m_ingredientReplacementCD;
            std::vector<Kitchen> m_kitchens;
            std::vector<IPizza> m_commands;
    };
}
