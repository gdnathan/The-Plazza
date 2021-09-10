/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Kitchen
*/

#pragma once

#include <thread>

#include "ArgParse.hpp"
#include "Cook.hpp"
#include "FoodStock.hpp"
#include "MultiThread/NamedPipe.hpp"
#include "Pizza.hpp"
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>

namespace Plazza
{
class Kitchen {
  public:
    Kitchen(params_t params, int id);
    Kitchen(Kitchen const& to_copy) = delete;
    Kitchen(Kitchen&& to_move) = delete;

    ~Kitchen();

    Kitchen& operator=(Kitchen const& to_copy) = delete;
    Kitchen& operator=(Kitchen&& to_move) = delete;

    /*
     * main function of the kitchen, the one to call after fork()
     */
    void run();
    void stop();

  private:
    /*
     * print occupancy of the cooks, and stock of ingredients
     */
    void status() noexcept;
    /*
     * get the number of pizzas currently in the kitchen, and send the result
     * througt the write pipe.
     */
    void getPizzaNbr() noexcept;
    /*
     * read pizza name from [name] and try to save it in the queue. Send TRUE if
     * the kitchen can handle the command, FALSE otherwise.
     */
    void handlePizza(const std::string& name);

    bool getlineAsync();
    // Checks if any of the cooks are busy
    bool AreCooksActive();
    bool IsKitchenActive();
    // Checks if all the cooks have been out of work for 4 seconds.
    bool ShouldKitchenClose();

    bool CookManager(std::tuple<Pizza, Ingredients_t, int>);
    /*
     * have a clock, and call for refill every x ms
     */
    std::vector<Cook> Cooks;
    bool tryRefill() noexcept;
    int pizzaNb = 0;
    const int cookNb = 0;
    const int refillTime;
    const int CookTimeMultiplier;
    int id;
    bool running = true;
    std::optional<NamedPipe> read;
    std::optional<NamedPipe> write;
    std::queue<Pizza> queue;
    FoodStock Stock;
};
} // namespace Plazza
