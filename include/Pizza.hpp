/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IPizza
*/

#pragma once
#include <cstddef>
#include <map>
#include <string>

namespace Plazza
{
    struct Pizza {
        Pizza(
            std::map<std::string, int> &ingredients,
            std::string &name,
            std::string &size, std::size_t time)
            : m_ingredients(ingredients), m_name(name), m_size(size), m_cookingTime(time) {}
        std::map<std::string, int> m_ingredients;
        std::string &m_name;
        std::string &m_size;
        std::size_t m_cookingTime;
    };
}
