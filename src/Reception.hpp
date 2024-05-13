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
                _cookingTimeMult(cookingTimeMult),
                _cookPerKitchen(cookPerKitchen),
                _ingredientReplacementCD(replacementCD) {}
            ~Reception() = default;

            void loop();

        private:
            double _cookingTimeMult;
            int _cookPerKitchen;
            std::size_t _ingredientReplacementCD;
    };
}
