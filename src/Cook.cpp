/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include <chrono>
#include <iostream>
#include <unistd.h>
#include "Logger.hpp"

namespace Plazza
{

Cook::Cook()
{
    this->busy = false;
}

Cook::~Cook()
{
    if (this->t.joinable())
        this->t.join();
}

bool Cook::isBusy() noexcept
{
    return this->busy.load();
}

void Cook::bake(int timeMs) noexcept
{
    this->busy.store(true, std::memory_order_relaxed);
    if (t.joinable()) {
        t.join();
    }
    t = std::move(std::thread(&Cook::baking, this, timeMs));

}

void Cook::baking(int time)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    this->busy.store(false, std::memory_order_relaxed);
    Logger::logfile("\r A cook has finished baking a pizza. Cooked for" + std::to_string(time) + " ms.\n");
}
}
