/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** argparse_tests
*/

#include "ArgParse.hpp"
#include "gtest/gtest.h"

TEST(argparse, normal_args)
{
    ASSERT_EQ(ArgParse::isArgsNumberCorrect(4),
              true); // Checks if 4 arguments is valid
}

TEST(argparse, print_help)
{
    params_t params;
    params.chefs_nbr = 3;
    params.stock_refill_time = 400;
    params.multiplier = 0.2;
    char* argv[] = {(char*)"Plazza", (char*)"0.2", (char*)"3", (char*)"400"};
    params_t new_params = ArgParse::ParseArgs(argv);
    ASSERT_EQ(new_params.chefs_nbr, params.chefs_nbr);
}