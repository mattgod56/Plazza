/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue
*/

#include "MessageQueue.hpp"

Plazza::MessageQueue::MessageQueue(std::string name, int max, int msgmax) : m_name(name), m_msgsize(msgmax)
{
    m_attr.mq_curmsgs = 0;
    m_attr.mq_flags = 0;
    m_attr.mq_maxmsg = max;
    m_attr.mq_msgsize = msgmax;

    m_queue = mq_open(name.c_str(), O_CREAT | O_RDWR, 0664, &m_attr);
    if (m_queue == (mqd_t)-1) {
        std::cout << strerror(errno) << std::endl;
        return;
    }
}

Plazza::MessageQueue::~MessageQueue()
{
    if (m_queue != (mqd_t)-1)
        mq_close(m_queue);
    if (m_queue != (mqd_t)-1)
        mq_unlink(m_name.c_str());
}
