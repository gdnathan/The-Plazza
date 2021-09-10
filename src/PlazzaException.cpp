/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** PlazzaException
*/

#include "PlazzaException.hpp"

#include <iostream>
#include <string>

namespace Plazza
{
PlazzaException::PlazzaException(const char* msg) : msg_(msg)
{}

PlazzaException::PlazzaException(const std::string& msg) : msg_(msg)
{}

const char* PlazzaException::what() const noexcept
{
    return this->msg_.c_str();
}
}
