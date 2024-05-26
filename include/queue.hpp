/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** queue
*/

#pragma once

#define QUEUE_NAME "/Plazzaqueue"
#define QUEUE_SIZE 10
#define QUEUE_MSG_SIZE 1024
#define QUEUE_DATA_SIZE 30

namespace Plazza {
    enum QUEUE_MESSAGES {
        INFO_RES,
        INFO,
        PIZZA,
        STATUS,
        STATUS_RES,
        DEAD
    };
}