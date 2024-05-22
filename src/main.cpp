/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** main
*/

#include "Kitchen.hpp"
#include "MessageQueue.hpp"
#include "define.hpp"
#include "Reception.hpp"

int getArgs(char **av)
{
    std::size_t idx = 0;

    std::string current = av[1];
    double cookingTimeMult = std::stod(current, &idx);
    if (idx != current.size() || cookingTimeMult <= 0)
        return FAILURE;

    current = av[2];
    int cookPerKitchen = std::stoi(current, &idx);
    if (idx != current.size() || cookPerKitchen <= 0)
        return FAILURE;

    current = av[3];
    std::size_t replacementCD = std::stol(current, &idx);
    if (idx != current.size() || replacementCD <= 0)
        return FAILURE;

    Plazza::Reception reception(cookingTimeMult, cookPerKitchen, replacementCD);
    Plazza::Kitchen kitchen(cookPerKitchen, cookingTimeMult, replacementCD); //TEMPORARY THIS SHOULDN'T BE HERE
    kitchen.dailyKitchenLife(); //TEMPORARY THIS SHOULDN'T BE HERE
    reception.getCommands();
    return SUCCESS;
}

int main(int ac, char **av)
{
    if (ac != 4)
        return FAILURE;
    return getArgs(av);
}
