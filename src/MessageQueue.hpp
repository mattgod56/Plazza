/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue
*/

#pragma once

#include <sys/types.h>
#include <mqueue.h>
#include <string>

#define QUEUE_NAME "/plazzaqueue"
#define QUEUE_SIZE 10
#define QUEUE_MSG_SIZE 1024

namespace Plazza
{
    class MessageQueue {
        public:
            MessageQueue(std::string name, int max, int msgmax);
            ~MessageQueue();

            void sendMessage(std::string &);
            std::string receiveMessage(void);
        private:
            std::string m_name;
            int m_msgsize;
            mqd_t m_queue;
            struct mq_attr m_attr;
    };
}
