/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Reception
*/

#include "Reception.hpp"
#include "Logger.hpp"

#include <cstdint>
#include <string.h>

#include <algorithm>
#include <errno.h>
#include <iostream>
#include <list>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#include "ArgParse.hpp"
#include "PlazzaException.hpp"

namespace Plazza
{
Reception::Reception(params_t params)
{
    this->params = params;
}

Reception::~Reception()
{
    for (auto it = this->kitchens.begin(); it != this->kitchens.end(); it++)
        it->stop();
}

std::vector<std::string> Reception::split(const std::string& src,
                                          char delimiter) noexcept
{
    std::vector<std::string> res;
    std::string tmp;
    std::istringstream streamator(src);

    while (std::getline(streamator, tmp, delimiter))
        res.push_back(tmp);
    return res;
}

void Reception::printStatus() noexcept
{
    int idx = 1;
    if (kitchens.empty())
        Logger::LogError("Couldn't print status. No kitchens are currently avilable.");
    for (auto& i: kitchens) {
        Logger::log("Kitchen #" + std::to_string(idx));
        idx++;
        i.printStatus();
    }
}

static void printHelp()
{
    Logger::log("Pizza ordering MUST respect the following grammar:\n"
                "S := TYPE SIZE NUMBER[; TYPE SIZE NUMBER]* TYPE :\n"
                "Type\t= [a..zA..Z] + SIZE :\n"
                "Size\t= S | M | L | XL | XXL NUMBER :\n"
                "Number\t= x[1..9][0..9] *\n"
                "Ordering example which is grammatically valid:\n"
                "regina XXL x2; fantasia M x3; margarita S x1");
}

PizzaCmd_t Reception::getCommandFromString(const std::string str)
{
    std::vector<std::string> parsed = this->split(str, ' ');
    PizzaCmd_t command;

    if (parsed.size() != 3)
        throw(PlazzaException("Invalid command. Type 'help' to view help."));

    bool isIn = false;
    for (auto& i: {"S", "M", "L", "XL", "XXL"}) {
        if (i == parsed[1])
            isIn = true;
    }
    if (!isIn) {
        throw(PlazzaException("Unknown pizza size."));
    }
    try {
        for (auto& i: {
                 "regina",
                 "fantasia",
                 "margarita",
                 "americana",
             }) {
            if (i == parsed[0])
                command.type = parsed[0];
        }
        if (command.type == "NULL")
            throw(PlazzaException("Unknown Pizza type."));
        command.number = std::stoi(parsed[2].substr(1));
    } catch (std::invalid_argument&) {
        throw(PlazzaException("Invalid number of pizza"));
    }
    return command;
}

static std::string trim(const std::string& s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

Action Reception::checkLine(std::string input) noexcept
{
    if (input == "help")
        return Action::HELP;
    if (input == "status")
        return Action::STATUS;
    if (input == "exit")
        return Action::EXIT;
    auto commands = split(input, ';');
    for (auto& token: commands) {
        token = trim(token);
        try {
            Commands.push_back(getCommandFromString(token));
        } catch (PlazzaException& e) {
            Logger::LogError(e.what());
            Commands.clear();
            return Action::NONE;
        }
    }
    return Action::RUN;
}

bool Reception::assignToKitchen(PizzaCmd_t command)
{
    int best_nbr = INT32_MAX;
    std::list<KitchenConnect>::iterator best_it;

    for (auto it = this->kitchens.begin(); it != this->kitchens.end(); it++) {
        int tmp = it->getPizzaNbr();
        if (static_cast<unsigned int>(tmp) < this->params.chefs_nbr &&
            tmp < best_nbr) {
            best_nbr = tmp;
            best_it = it;
        }
    }
    if (best_nbr == INT32_MAX) {
        return false;
    }
    return best_it->addPizza(command.type);
}

void Reception::assignToNewKitchen(PizzaCmd_t command)
{
    this->kitchens.emplace_back(this->params, this->kitchens.size());
    if (!this->kitchens.back().addPizza(command.type))
        throw std::logic_error("Fatal error: New Kitchen is full at creation");
}

void Reception::manageCommands()
{
    for (auto const& command: Commands) {
        for (int i = 0; i < command.number; i++) {
            if (!this->assignToKitchen(command)) {
                this->assignToNewKitchen(command);
            }
        }
    }
}

void Reception::CheckKichenActivity()
{
    for (std::list<KitchenConnect>::iterator it = this->kitchens.begin();
         it != this->kitchens.end();) {
        if (!it->IsActive()) {
            it = this->kitchens.erase(it++);
        } else {
            ++it;
        }
    }
}

int Reception::run() noexcept
{
    std::string line;
    Action action = Action::NONE;
    Logger::log("$> ", false, true);
    while (getline(std::cin, line)) {
        Logger::logfile(line);
        CheckKichenActivity();
        try {
            action = this->checkLine(line);
        } catch (PlazzaException& e) {
            Logger::LogError(e.what());
        }
        switch (action) {
            case Action::EXIT:
                return 0;
            case Action::HELP:
                printHelp();
                break;
            case Action::STATUS:
                this->printStatus();
                break;
            case Action::RUN:
                this->manageCommands();
                Commands.clear();
                break;
            default:
                break;
        }
        // make algo with each elem of _Commands for (auto const &elem :
        // commands)
        Logger::log("\n$> ", false, true);
    }
    Logger::log("[" + std::to_string(errno) + "]");
    return 0;
}
} // namespace Plazza
