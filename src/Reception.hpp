/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#pragma once

#include <memory>
#include <vector>

#include "Kitchen.hpp"

namespace Plazza {

    class Reception {
        public:
            Reception(double cookingTimeMult, int cookPerKitchen, std::size_t replacementCD):
                m_cookingTimeMult(cookingTimeMult),
                m_cookPerKitchen(cookPerKitchen),
                m_ingredientReplacementCD(replacementCD),
                m_ctr(0) {}
            ~Reception() = default;

            void getCommands();
            void checkCommand(std::string str);
            void pizzaFound(std::istringstream &iss, Pizza &pizza);
            void statusCmd(void);
            void communicateToKitchen(Plazza::Pizza &);
            void deleteKitchen(void);
        private:
            void createKitchen(Plazza::Pizza &pizza);
            double m_cookingTimeMult;
            int m_cookPerKitchen;
            std::size_t m_ingredientReplacementCD;
            int m_ctr;
            std::vector<std::unique_ptr<Plazza::Kitchen>> m_kitchens;
            std::vector<Plazza::Pizza> m_commands;
    };
}
