/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Process
*/

#include <sys/types.h>

namespace Plazza
{
    class Process {
        public:
            void startProcess(void);
            void stopProcess(void);
            int getPid(void);
        private:
            int m_pid;
    };
}
