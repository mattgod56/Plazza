/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Process
*/

#include "Process.hpp"
#include <unistd.h>
#include <stdlib.h>

int Plazza::Process::getPid(void)
{
    return m_pid;
}

void Plazza::Process::startProcess(void)
{
    m_pid = fork();
}

void Plazza::Process::stopProcess(void)
{
    if (m_pid == 0) {
        exit(0);
    }
}
