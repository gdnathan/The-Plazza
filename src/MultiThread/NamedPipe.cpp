/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** NamedPipe
*/

#include "MultiThread/NamedPipe.hpp"

NamedPipe::NamedPipe(int id, Type_t type, bool parent)
{
    this->type = type;
    this->parent = parent;
    this->fifo = "fifo_" + std::to_string(id) +
                 std::string(parent ? (type == READ ? "0" : "1")
                                    : (type == READ ? "1" : "0"));
    if (parent) {
        remove(this->fifo.data());
        if (mkfifo(this->fifo.data(), 0667) == -1) {
            throw std::system_error();
        }
    }
    this->writefd = -1;
    this->readfd = -1;
}

NamedPipe::NamedPipe(NamedPipe&& to_move)
{
    this->parent = to_move.parent;
    this->writefd = to_move.writefd;
    to_move.writefd = -1;
    this->readfd = to_move.readfd;
    to_move.readfd = -1;
    this->fifo = to_move.fifo;
    this->type = to_move.type;
}

NamedPipe& NamedPipe::operator=(NamedPipe&& to_move)
{
    this->parent = to_move.parent;
    this->writefd = to_move.writefd;
    to_move.writefd = -1;
    this->readfd = to_move.readfd;
    to_move.readfd = -1;
    this->fifo = to_move.fifo;
    this->type = to_move.type;
    return *this;
}

NamedPipe::~NamedPipe()
{
    if (writefd != -1)
        close(writefd);
    if (readfd != -1)
        close(readfd);
}
void NamedPipe::openPipe()
{
    if (this->type == READ) {
        readfd = open(fifo.data(), O_RDONLY);
        if (readfd < 0)
            throw(Plazza::PlazzaException("Error while oppenning read " + fifo));
    } else {
        writefd = open(fifo.data(), O_WRONLY);
        if (writefd < 0)
            throw(Plazza::PlazzaException("Error while oppenning write " + fifo));
    }
}
void NamedPipe::send(std::string msg)
{
    write(this->writefd, msg.data(), msg.size());
}

std::string& NamedPipe::unpack(std::string& src)
{
    return src;
}

std::string& NamedPipe::pack(std::string& src)
{
    return src;
}

std::istream& operator>>(std::istream& input, NamedPipe&)
{
    return input;
}
std::ostream& operator<<(std::ostream& output, const NamedPipe&)
{
    return output;
}

std::string NamedPipe::get()
{
    char buf[10] = "\0\0\0\0\0\0\0\0\0";
    read(readfd, buf, 9);
    return buf;
}

bool NamedPipe::tryGet(std::string& save)
{
    struct pollfd ufd;
    ufd.fd = this->readfd;
    ufd.events = POLLIN;

    if (poll(&ufd, 1, 100) == 0) {
        return false;
    }
    save = this->get();
    return true;
}
