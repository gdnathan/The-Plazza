/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** IException
*/

#pragma once

#include <exception>
#include <string>

namespace Plazza
{
class PlazzaException : public std::exception {
  public:
    PlazzaException(const char* msg);
    PlazzaException(const std::string& msg);
    ~PlazzaException() noexcept = default;

    const char* what() const noexcept;

  private:
    const std::string msg_;
};
}
