/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** IArgParse
*/

#pragma once
#include <string>

struct params_t
{
    float multiplier;
    unsigned int chefs_nbr;
    unsigned int stock_refill_time;
};

class ArgParse {
  public:
    static bool isArgsNumberCorrect(int ac) noexcept;
    static params_t ParseArgs(char** args);
    static void printHelp() noexcept;

  private:
};
