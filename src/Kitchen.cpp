/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "Pizza.hpp"

void Plazza::Kitchen::assignCommand(Plazza::Pizza &pizza)
{
    return;
}

void Plazza::Kitchen::ingredientsRefill(void)
{
    return;
}

void Plazza::Kitchen::waitForCommand(void)
{
    Plazza::Pizza piz;

    while (true) {
        piz = m_queue.receiveMessage<Plazza::Pizza>();
    }
}