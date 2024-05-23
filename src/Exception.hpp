/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Exception
*/

#pragma once

#include <exception>
namespace Plazza
{
    class MessageQueueError : public std::exception {
        public:
            const char *what() const noexcept override
            {
                return "Error during message queue";
            }
    };
}
