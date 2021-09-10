/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "PlazzaException.hpp"
#include <algorithm>
#include "Logger.hpp"
#include <chrono>
#include <iostream>
#include <tuple>
#include <unistd.h>

namespace Plazza
{
Kitchen::Kitchen(params_t params, int id) :
    Cooks(params.chefs_nbr),
    cookNb(params.chefs_nbr),
    refillTime(params.stock_refill_time),
    CookTimeMultiplier(params.multiplier)
{
    this->id = id;
    this->Stock.refill();
    this->Stock.refill();
    this->Stock.refill();
    this->Stock.refill();
    this->Stock.refill();
}

Kitchen::~Kitchen()
{
}

void Kitchen::status(void) noexcept
{
    Plazza::Ingredients_t i = this->Stock.getIngredients();
        Logger::log("Ingredients:\n"
                  "D:" + std::to_string(i.Does) + "\tT:" +
                  std::to_string(i.Tomatoes) + "\tG:" +
                  std::to_string(i.Gruyere) + "\nH:" +
                  std::to_string(i.Ham) + "\tM:" +
                  std::to_string(i.Mushrooms) + "\tS:" +
                  std::to_string(i.Steak) + "\nE:" +
                  std::to_string(i.Eggplant) + "\tGC:" +
                  std::to_string(i.GoatCheese)
                   + "\tCL:" + std::to_string(i.ChiefLove));

    for (auto& i: this->Cooks)
        std::cout << (i.isBusy() ? "\033[31m •\033[0m" : "\033[32m •\033[0m");
    std::cout << std::endl;
    this->write->send("OK");
}


void Kitchen::getPizzaNbr() noexcept
{
    this->write->send(std::to_string(this->pizzaNb));
}

using attr = std::tuple<Pizza, Ingredients_t, int>;

bool Kitchen::CookManager(attr attrs)
{
    int i = 0;
    for (auto cook = this->Cooks.begin(); cook != this->Cooks.end(); cook++) {
        if ((!cook->isBusy()) &&
            this->Stock.tryConsumeIngredients(std::get<1>(attrs))) {
            cook->bake(std::get<2>(attrs) * this->CookTimeMultiplier);
            this->pizzaNb -= 1;
            return true;
        }
        i++;
    }
    return false;
}

attr getPizzaAttributes(const Pizza& pizza)
{
    auto attributes =
        std::find_if(pizzas.begin(), pizzas.end(), [=](auto item) {
            return std::get<0>(item) == pizza;
        });
    if (attributes not_eq pizzas.end()) {
        return *attributes;
    }
    throw(PlazzaException("Unknown Pizza type."));
}

void Kitchen::handlePizza(const std::string& name)
{
    if (name.empty()) {
        Logger::log("Empty Pizza name caught by kitchen");
    }
    if (this->pizzaNb > this->cookNb) {
        this->write->send("FALSE");
        return;
    }
    this->write->send("TRUE");
    Pizza pizza;
    try {
        pizza = PizzaType.at(name);
    } catch (std::out_of_range&) {
        Logger::log("Unknown pizza: " + name);
        return;
    }
    this->queue.push(pizza);
    this->pizzaNb += 1;
}

void Kitchen::stop()
{
    running = false;
}

bool Kitchen::AreCooksActive()
{
    for (auto& i: this->Cooks)
        if (i.isBusy())
            return true;
    return false;
}

bool Kitchen::ShouldKitchenClose()
{
    static auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    if (AreCooksActive()) {
        t1 = std::chrono::high_resolution_clock::now();
        return false;
    }
    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) >=
        std::chrono::milliseconds(4000)) {
        return true;
    }
    return false;
}

void Kitchen::run()
{
    std::string commandLine;

    this->read = NamedPipe(id, NamedPipe::READ, false);
    this->write = NamedPipe(id, NamedPipe::WRITE, false);
    this->write->openPipe();
    this->read->openPipe();
    while (this->running) {
        this->tryRefill();
        if (ShouldKitchenClose()) {
            return;
        }
        if (this->read->tryGet(commandLine)) {
            if (commandLine == "")
                return;
            if (commandLine == "STATUS")
                this->status();
            else if (commandLine == "PIZZANBR")
                this->getPizzaNbr();
            else if (commandLine == "STOP")
                return;
            else {
                this->handlePizza(commandLine);
            }
        }
        if (!queue.empty()) {
            Pizza tmp = this->queue.front();
            attr attributes = getPizzaAttributes(tmp);
            if (this->CookManager(attributes)) {
                this->queue.pop();
            }
        }
    }
}

bool Kitchen::tryRefill() noexcept
{
    static auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();

    if (std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1) >=
        std::chrono::milliseconds(this->refillTime)) {
        t1 = std::chrono::high_resolution_clock::now();
        this->Stock.refill();
        return true;
    }
    return false;
}
}
