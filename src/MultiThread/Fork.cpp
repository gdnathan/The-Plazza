/*
** EPITECH PROJECT, 2021
** B-CCP-400-BDX-4-1-theplazza-thomas.camlong
** File description:
** Fork
*/

#include "MultiThread/Fork.hpp"
#include <sys/wait.h>

int Fork::plazzaFork()
{
    int i = fork();
    if (i < 0) {
        throw(Plazza::PlazzaException("System Error: fork failed"));
    }
    return i;
}

int Fork::plazzaWait(int pid)
{
    return waitpid(pid, NULL, WNOHANG);
}
