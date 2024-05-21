/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue
*/

#pragma once

#include <cstring>
#include <sys/types.h>
#include <mqueue.h>
#include <iostream>
#include <string>

namespace Plazza
{
    class MessageQueue {
        public:
            MessageQueue(std::string name, int max, int msgmax);
            ~MessageQueue();

            template<typename T>
            void sendMessage(T &buffer, std::size_t length)
            {
                char buff[length + 1];
                memcpy(&buff, &buffer, length);

                if (mq_send(m_queue, buff, length, 0) == -1) {
                    std::cout << strerror(errno) << std::endl;
                }
            }

            template<typename D>
            D receiveMessage(void)
            {
                char buffer[m_msgsize + 1];
                D res;

                if (m_queue != (mqd_t)-1) {
                    ssize_t bytes =  mq_receive(m_queue, buffer, m_msgsize, NULL);
                    if (bytes == -1) {
                        std::cout << strerror(errno) << std::endl;
                        throw;
                    }
                    memcpy(&res, buffer, bytes);
                }
                return res;
            }
        private:
            std::string m_name;
            int m_msgsize;
            mqd_t m_queue;
            struct mq_attr m_attr;
    };
}
