/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "MultiThread/KitchenConnect.hpp"
#include "Pizza.hpp"
#include <chrono>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

namespace Plazza
{
enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

enum Action
{
    NONE = 0,
    HELP,
    STATUS,
    EXIT,
    RUN,
};

struct PizzaCmd_t
{
    std::string type = "NULL";
    PizzaSize size = S;
    int number;
};

class Reception {
  public:
    Reception(params_t param);
    Reception(Reception const& to_copy) = delete;
    Reception(Reception&& to_move) = delete;

    ~Reception();

    Reception& operator=(Reception const& to_copy) = delete;

    /*
     * entrypoint of the Reception
     */
    int run() noexcept;

  private:
    /*
     * read the input, and return the action to execute
     */
    Action checkLine(std::string command) noexcept;
    /*
     * print the status of kitchens
     */
    void printStatus() noexcept;

    /*
     * split the string s according to the delimitor, into a vector of string
     */
    std::vector<std::string> split(const std::string& s,
                                   char delimitor) noexcept;
    /*
     * pop every commands from Commands, and send them to kicthens
     */
    void manageCommands();
    /*
     * parse the string str and return a command structure.
     * throw if any error happend
     */
    PizzaCmd_t getCommandFromString(const std::string str);
    /*
     * check for available kitchen to send the command
     * loop over all kitchen to find the most suitable one
     */
    bool assignToKitchen(PizzaCmd_t command);
    /*
     * in case assignToKitchen fail, create a new kitchen, and assign it the
     * command.
     */
    void assignToNewKitchen(PizzaCmd_t command);

    void CheckKichenActivity();

    std::vector<PizzaCmd_t> Commands;
    std::list<KitchenConnect> kitchens;
    params_t params;
};

}

#endif /* !RECEPTION_HPP_ */
