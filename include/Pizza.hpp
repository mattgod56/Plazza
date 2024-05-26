/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** IPizza
*/

#pragma once
#include <map>
#include <string>

#define INGREDIENTS_NBR 9

namespace Plazza
{
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    enum PizzaIngredients
    {
        Dough,
        Tomato,
        Gruyere,
        Ham,
        Mushroom,
        Steak,
        Eggplant,
        GoatCheese,
        ChiefLove,
        NONE
    };

    const std::map<PizzaType, std::string> typeToString = {
        {PizzaType::Regina, "regina"},
        {PizzaType::Margarita, "margarita"},
        {PizzaType::Americana, "americana"},
        {PizzaType::Fantasia, "fantasia"}
    };

    const std::map<std::string, PizzaType> stringToType = {
        {"regina", PizzaType::Regina},
        {"margarita", PizzaType::Margarita},
        {"americana", PizzaType::Americana},
        {"fantasia", PizzaType::Fantasia}
    };

    const std::map<PizzaSize, std::string> sizeToString = {
        {PizzaSize::S, "S"},
        {PizzaSize::M, "M"},
        {PizzaSize::L, "L"},
        {PizzaSize::XL, "XL"},
        {PizzaSize::XXL, "XXL"}
    };

    const std::map<std::string, PizzaSize> stringToSize = {
        {"S", PizzaSize::S},
        {"M", PizzaSize::M},
        {"L", PizzaSize::L},
        {"XL", PizzaSize::XL},
        {"XXL", PizzaSize::XXL}
    };

    const std::map<PizzaIngredients, std::string> ingredientToString = {
        {PizzaIngredients::Dough, "dough"},
        {PizzaIngredients::Eggplant, "eggplant"},
        {PizzaIngredients::GoatCheese, "goat cheese"},
        {PizzaIngredients::Gruyere, "gruyere"},
        {PizzaIngredients::ChiefLove, "chief love"},
        {PizzaIngredients::Ham, "ham"},
        {PizzaIngredients::Mushroom, "mushroom"},
        {PizzaIngredients::Steak, "steak"},
        {PizzaIngredients::Tomato, "tomato"}
    };

    const std::map<std::string, PizzaIngredients> stringToIngredient = {
        {"dough", PizzaIngredients::Dough},
        {"eggplant", PizzaIngredients::Eggplant},
        {"goat cheese", PizzaIngredients::GoatCheese},
        {"gruyere", PizzaIngredients::Gruyere},
        {"chief love", PizzaIngredients::ChiefLove},
        {"ham", PizzaIngredients::Ham},
        {"mushroom", PizzaIngredients::Mushroom},
        {"steak", PizzaIngredients::Steak},
        {"tomato", PizzaIngredients::Tomato}
    };

    struct Pizza {
        Pizza() = default;
        Pizza(
            std::map<PizzaIngredients, int> ingredients,
            PizzaType type,
            PizzaSize size, std::size_t time)
            : m_ingredients(ingredients), m_type(type), m_size(size), m_cookingTime(time) {}
        std::map<PizzaIngredients, int> m_ingredients;
        PizzaType m_type;
        PizzaSize m_size;
        std::size_t m_cookingTime;
    };

    const Pizza menu[] = {
        Pizza({{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Ham, 1}, {Mushroom, 1}}, PizzaType::Regina, PizzaSize::S, 2),
        Pizza({{Dough, 1}, {Tomato, 1}, {Gruyere, 1}}, PizzaType::Margarita, PizzaSize::S, 1),
        Pizza({{Dough, 1}, {Tomato, 1}, {Gruyere, 1}, {Steak, 1}}, PizzaType::Americana, PizzaSize::S, 2),
        Pizza({{Dough, 1}, {Tomato, 1}, {Eggplant, 1}, {GoatCheese, 1}, {ChiefLove, 1}}, PizzaType::Fantasia, PizzaSize::S, 4)
    };
}
