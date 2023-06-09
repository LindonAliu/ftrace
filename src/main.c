/*
** EPITECH PROJECT, 2023
** main
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

static int exec_command(int *pid, char *command[])
{
    *pid = fork();
    if (*pid == 0) {
        if (ptrace(PT_TRACE_ME, 0, NULL, NULL) < 0)
            return -1;
        raise(SIGSTOP);
        setenv("LD_BIND_NOW", "1", 1);
        execvp(command[0], command);
        perror(command[0]);
        return -1;
    }
    return 0;
}

int main(int ac, char *av[])
{
    struct settings s = {0};
    pid_t pid;

    if (ac < 2)
        return PRINT("%s: must have PROG [ARGS] or -p PID.\n", av[0]), 84;
    av += parse_options(ac, av, &s);
    if (strcmp(av[0], "-p") == 0) {
        if (av[1] == NULL)
            return 84;
        pid = atoi(av[1]);
        av += 2;
        if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) < 0)
            return -1;
    } else if (exec_command(&pid, av) < 0)
        return 84;
    return ftrace(pid, &s) == 0 ? 0 : 84;
}
