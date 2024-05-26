/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** MessageQueue
*/

#include "MessageQueue.hpp"
#include "Exception.hpp"

#include <iostream>
#include <cstring>
#include <mqueue.h>

Plazza::MessageQueue::MessageQueue(std::string name, int max, int msgmax) : m_name(name), m_msgsize(msgmax)
{
    m_attr.mq_curmsgs = 0;
    // m_attr.mq_flags = O_NONBLOCK;
    m_attr.mq_maxmsg = max;
    m_attr.mq_msgsize = msgmax;

    dprintf(1, "init queue %s\n", name.c_str());
    m_queue = mq_open(name.c_str(), O_CREAT | O_RDWR | O_NONBLOCK, 0664, &m_attr);
    if (m_queue == (mqd_t)-1) {
        std::cout << strerror(errno) << std::endl;
        throw Plazza::MessageQueueError();
    }
}

Plazza::MessageQueue::~MessageQueue()
{
    if (m_queue != (mqd_t)-1)
        mq_close(m_queue);
    if (m_queue != (mqd_t)-1)
        mq_unlink(m_name.c_str());
}

void Plazza::MessageQueue::sendMessage(int code, std::array<int, QUEUE_DATA_SIZE> &data)
{
    MessageQueue::Datapack buffer;
    buffer.replycode = code;
    for (int i = 0; i < QUEUE_DATA_SIZE; i++)
        buffer.data[i] = data[i];
    if (m_queue != (mqd_t)-1) {
        if (mq_send(m_queue, (const char *)&buffer, sizeof(buffer), 0) == -1) {
            std::cerr << "send: " << strerror(errno) << std::endl;
            throw Plazza::MessageQueueError();
        }
    }
}

Plazza::MessageQueue::Datapack Plazza::MessageQueue::receiveMessage(void)
{
    Plazza::MessageQueue::Datapack res;

    if (m_queue != (mqd_t)-1) {
        // dprintf(1, "want data %d\n", m_msgsize);
        ssize_t bytes =  mq_receive(m_queue, (char *)&res, m_msgsize, NULL);
        // dprintf(1,"got data\n");
        if (bytes == -1) {
            std::cerr << "receive: " << strerror(errno) << std::endl;
            throw Plazza::MessageQueueError();
        }
    }
    dprintf(1, "return from message\n");
    return res;
}
