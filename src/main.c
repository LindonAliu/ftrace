/*
** EPITECH PROJECT, 2023
** main
** File description:
** FreeKOSOVO
*/

#include "strace.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

static int exec_command(int *pid, const char *command[])
{
    *pid = fork();
    if (*pid == 0) {
        if (ptrace(PT_TRACE_ME, 0, NULL, NULL) < 0)
            return -1;
        raise(SIGSTOP);
        execvp(command[0], (char * const *)command);
        perror(command[0]);
        return -1;
    }
    return 0;
}

int main(int ac, const char *av[])
{
    struct settings s = {0};
    pid_t pid;

    if (ac < 2)
        return 84;
    av++;
    if (strcmp(av[0], "-s") == 0) {
        s.pretty_args = true;
        av++;
    }
    if (strcmp(av[0], "-p") == 0) {
        if (av[1] == NULL)
            return 84;
        pid = atoi(av[1]);
        av += 2;
        if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) < 0)
            return -1;
    } else if (exec_command(&pid, av) < 0)
        return 84;
    return strace(pid, &s) == 0 ? 0 : 84;
}
