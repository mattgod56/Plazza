/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue
*/

#pragma once

#include "queue.hpp"
#include <array>
#include <mqueue.h>
#include <string>

namespace Plazza
{
    class MessageQueue {
        public:
            struct Datapack {
                int replycode;
                int data[QUEUE_DATA_SIZE];
            };
            MessageQueue(std::string name, int max, int msgmax);
            ~MessageQueue();

            void sendMessage(int code, std::array<int, QUEUE_DATA_SIZE> &data);

            MessageQueue::Datapack receiveMessage(void);

            void operator<<(MessageQueue::Datapack &data)
            {
                std::array<int, QUEUE_DATA_SIZE> arr;
                for (int i = 0; i < QUEUE_DATA_SIZE; i++)
                    arr[i] = data.data[i];
                sendMessage(data.replycode, arr);
            }

            void operator>>(MessageQueue::Datapack &data)
            {
                data = receiveMessage();
            }
            private:
                std::string m_name;
                int m_msgsize;
                mqd_t m_queue;
                struct mq_attr m_attr;
    };
}
