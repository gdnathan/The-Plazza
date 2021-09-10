/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** FoodStuck
*/

#include "FoodStock.hpp"
#include <iostream>

namespace Plazza
{
FoodStock::FoodStock()
{
    return;
}

bool FoodStock::tryConsumeIngredients(const Ingredients_t& i)
{
    int Does = Ingredients.Does - i.Does;
    int Tomatoes = Ingredients.Tomatoes - i.Tomatoes;
    int Gruyere = Ingredients.Gruyere - i.Gruyere;
    int Ham = Ingredients.Ham - i.Ham;
    int Mushrooms = Ingredients.Mushrooms - i.Mushrooms;
    int Steak = Ingredients.Steak - i.Steak;
    int Eggplant = Ingredients.Eggplant - i.Eggplant;
    int GoatCheese = Ingredients.GoatCheese - i.GoatCheese;
    int ChiefLove = Ingredients.ChiefLove - i.ChiefLove;
    if (Does < 0 || Tomatoes < 0 || Gruyere < 0 || Ham < 0 || Mushrooms < 0 ||
        Steak < 0 || Eggplant < 0 || GoatCheese < 0 || ChiefLove < 0)
        return false;
    Ingredients.Does = Does;
    Ingredients.Tomatoes = Tomatoes;
    Ingredients.Gruyere = Gruyere;
    Ingredients.Ham = Ham;
    Ingredients.Mushrooms = Mushrooms;
    Ingredients.Steak = Steak;
    Ingredients.Eggplant = Eggplant;
    Ingredients.GoatCheese = GoatCheese;
    Ingredients.ChiefLove = ChiefLove;
    return true;
}

const Ingredients_t& FoodStock::getIngredients()
{
    return Ingredients;
}

void FoodStock::refill()
{
    Ingredients.Does += 1;
    Ingredients.Tomatoes += 1;
    Ingredients.Gruyere += 1;
    Ingredients.Ham += 1;
    Ingredients.Mushrooms += 1;
    Ingredients.Steak += 1;
    Ingredients.Eggplant += 1;
    Ingredients.GoatCheese += 1;
    Ingredients.ChiefLove += 1;
    return;
}
}
