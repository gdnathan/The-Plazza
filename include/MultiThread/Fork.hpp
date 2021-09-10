/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** Fork
*/

#pragma once
#include "PlazzaException.hpp"
#include <unistd.h>
#include <iostream>

class Fork {
  public:
    Fork() = default;
    ~Fork() = default;
    static int plazzaFork();
    static int plazzaWait(int pid);
};
