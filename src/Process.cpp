/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Process
*/

#include "Process.hpp"
#include <cerrno>
#include <cstring>
#include <unistd.h>
#include <iostream>

int Plazza::Process::getPid(void)
{
    return m_pid;
}

void Plazza::Process::startProcess(void)
{
    m_pid = fork();
    if (m_pid == -1) {
        std::cerr << strerror(errno) << std::endl;
    }
}

void Plazza::Process::stopProcess(void)
{
    if (m_pid == 0) {
        exit(0);
    }
}
