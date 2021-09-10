/*
** EPITECH PROJECT, 2021
** Plazza [SSH: elitebook]
** File description:
** logger_test
*/

#include "Logger.hpp"
#include "gtest/gtest.h"

TEST(Logger, ok)
{
    Logger::log("This is being logged.");
    ASSERT_EQ(0, 0);
}