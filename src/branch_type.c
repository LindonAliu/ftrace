/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "stdio.h"

#include <stddef.h>
#include <sys/ptrace.h>
#include <sys/user.h>

int is_internal_function(pid_t pid, struct user_regs_struct *regs)
{
    long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    res &= 0xff;
    if (res == 0xe8 || res == 0xff || res == 0x9a)
        return 1;
    return 0;
}
