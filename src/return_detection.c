/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "stdio.h"
#include "ftrace.h"

#include <sys/user.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <unistd.h>

bool is_return(pid_t pid, struct user_regs_struct *regs)
{
    long long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    res &= 0xff;
    if (res == 0xc3 || res == 0xcb)
        return 1;
    return 0;
}

int handle_return(pid_t pid, struct user_regs_struct *regs)
{
    char *function_name = NULL;

    PRINT("Leaving function %s\n", function_name);
}
