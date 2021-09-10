/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Pizza
*/

#pragma once

#include <array>
#include <string>
#include <utility>
#include <map>

#include "FoodStock.hpp"

namespace Plazza
{
enum class Pizza
{
    None = 0,
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

// int Does = 0;
// int Tomatoes = 0;
// int Gruyere = 0;
// int Ham = 0;
// int Mushrooms = 0;
// int Steak = 0;
// int Eggplant = 0;
// int GoatCheese = 0;
// int ChiefLove = 0;
//
static const std::map<std::string, Pizza> PizzaType = {
    {"regina", Pizza::Regina},
    {"fantasia", Pizza::Fantasia},
    {"margarita", Pizza::Margarita},
    {"americana", Pizza::Americana},
};

static const std::array<std::tuple<Pizza, Ingredients_t, int>, 5> pizzas = {
    std::tuple<Pizza, Ingredients_t, int>(Pizza::None, Ingredients_t{}, 0),
    std::tuple<Pizza, Ingredients_t, int>(Pizza::Margarita,
                                          Ingredients_t{.Does = 1,
                                                        .Tomatoes = 1,
                                                        .Gruyere = 1,
                                                        .ChiefLove = 0},
                                          1000),
    std::tuple<Pizza, Ingredients_t, int>(Pizza::Regina,
                                          Ingredients_t{.Does = 1,
                                                        .Tomatoes = 1,
                                                        .Gruyere = 1,
                                                        .Ham = 1,
                                                        .Mushrooms = 1,
                                                        .ChiefLove = 0},
                                          2000),
    std::tuple<Pizza, Ingredients_t, int>(Pizza::Americana,
                                          Ingredients_t{.Does = 1,
                                                        .Tomatoes = 1,
                                                        .Gruyere = 1,
                                                        .Steak = 1,
                                                        .ChiefLove = 0},
                                          2000),
    std::tuple<Pizza, Ingredients_t, int>(Pizza::Fantasia,
                                          Ingredients_t{.Does = 1,
                                                        .Tomatoes = 1,
                                                        .Gruyere = 1,
                                                        .Eggplant = 1,
                                                        .GoatCheese = 1,
                                                        .ChiefLove = 1},
                                          4000)};
}
