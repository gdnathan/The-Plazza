/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** foodstock_tests
*/

#include "FoodStock.hpp"
#include "gtest/gtest.h"

TEST(foodstock, refill)
{
    Plazza::FoodStock f;
    f.refill();
    ASSERT_EQ(f.getIngredients().Does, 1);
}

TEST(foodstock, getingredients)
{
    Plazza::FoodStock f;
    ASSERT_EQ(f.getIngredients().ChiefLove, 0);
}

TEST(foodstock, consumeOK)
{
    Plazza::FoodStock f;
    auto ingredients = f.getIngredients();
    ingredients.ChiefLove = 6;
    ASSERT_EQ(f.tryConsumeIngredients(ingredients), false);
}

TEST(foodstock, consumeKO)
{
    Plazza::FoodStock f;
    auto ingredients = f.getIngredients();
    f.refill();
    ingredients.ChiefLove = 1;
    ASSERT_EQ(f.tryConsumeIngredients(ingredients), true);
}