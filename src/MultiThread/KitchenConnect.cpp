/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** KitchenInterface
*/

#include "MultiThread/KitchenConnect.hpp"

namespace Plazza
{
KitchenConnect::KitchenConnect(params_t params, int id)// : kitchen(params, id)
    : write(id, NamedPipe::WRITE, true),
    read(id, NamedPipe::READ, true)
{
    this->id = id;
    int pid = Fork::plazzaFork();
    if (pid == -1) {
        throw std::system_error();
    }
    if (pid == 0) {
        Kitchen kitchen(params, id);
        kitchen.run();
        exit(0);
    }
    this->pid = pid;
    this->read.openPipe();
    this->write.openPipe();
}

bool KitchenConnect::IsActive()
{
    if (Fork::plazzaWait(this->pid) > 0) {
        return false;
    }
    return true;
}

void KitchenConnect::printStatus()
{
    if (!this->IsActive())
        return;
    this->write.send("STATUS\0");
    this->read.get();
}
int KitchenConnect::getPizzaNbr()
{
    if (!this->IsActive())
        return 9999999;
    this->write.send("PIZZANBR");
    std::string tmp = this->read.get();
    try {
        int nb = std::stoi(tmp);
        return nb;
    } catch (std::invalid_argument&) {
        Logger::LogError(tmp + " is an invalid pizza number.");
    }
    return 99;
}
void KitchenConnect::stop()
{
    if (!this->IsActive())
        return;
    this->write.send("STOP");
    Fork::plazzaWait(pid);
}

bool KitchenConnect::addPizza(std::string pizzaType)
{
    if (!this->IsActive())
        return false;
    this->write.send(pizzaType + "\0");
    return this->read.get() == "TRUE" ? true : false;
}
}
