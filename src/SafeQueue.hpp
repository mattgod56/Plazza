/*
** EPITECH PROJECT, 2024
** SafeQueue
** File description:
** SafeQueue
*/

#pragma once
#include "Pizza.hpp"
#include <vector>
#include <mutex>

class SafeQueue {
    public:
        SafeQueue() {}
        ~SafeQueue() = default;
        void push(Plazza::Pizza pizza)
        {
            std::unique_lock<std::mutex> lk(m_mut);
            m_vect.push_back(pizza);
        }

        bool tryPop(Plazza::Pizza &pizza)
        {
            std::unique_lock<std::mutex> lk(m_mut);
            if (m_vect.size() == 0)
                return false;
            pizza = m_vect.at(0);
            m_vect.erase(m_vect.begin());
            return true;
        }

        int length()
        {
            std::unique_lock<std::mutex> lk(m_mut);
            return m_vect.size();
        }

    private:
        std::vector<Plazza::Pizza> m_vect;
        std::mutex m_mut;
};
