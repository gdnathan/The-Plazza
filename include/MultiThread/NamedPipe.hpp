/*
** EPITECH PROJECT, 2021
** Plazza
** File description:
** NamedPipes
*/

#pragma once

#include "PlazzaException.hpp"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <poll.h>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

class NamedPipe {
  public:
    enum Type_t
    {
        WRITE,
        READ
    };
    NamedPipe(int id, Type_t type, bool parent);
    NamedPipe(NamedPipe const& to_copy) = delete;
    NamedPipe(NamedPipe&& to_move);

    ~NamedPipe();

    /* void initPipe(int id, Type_t type, bool parent); */
    void openPipe();

    NamedPipe& operator=(NamedPipe const& to_copy) = delete;
    NamedPipe& operator=(NamedPipe&& to_move);

    std::string &pack(std::string& src);
    std::string &unpack(std::string& src);
    void send(std::string msg);
    std::string get();
    bool tryGet(std::string& save);

  private:
    bool parent;
    int writefd;
    int readfd;
    Type_t type;
    std::string fifo;
};

std::istream& operator>>(std::istream& input, NamedPipe&);
std::ostream& operator<<(std::ostream& output, const NamedPipe&);
