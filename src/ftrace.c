/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "stdio.h"

#include <sys/ptrace.h>
#include <sys/user.h>
#include <stddef.h>
#include <sys/wait.h>

int next_instruction(pid_t pid)
{
    if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) < 0)
        return -1;
    if (waitpid(pid, NULL, 0) < 0)
        return -1;
    return 0;
}

static int is_syscall(pid_t pid, struct user_regs_struct *regs)
{
    long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    return ((res & 0xff) == 0x0f) && (((res >> 8) & 0xff) == 0x05);
}

static int read_instruction(pid_t pid,
    struct settings *set, struct user_regs_struct *regs)
{
    if (is_syscall(pid, regs)) {
        if (handle_syscall(regs, pid, set) < 0)
            return -1;
        return 0;
    }
    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return -1;
    return 0;
}

int read_instructions(pid_t pid, struct settings *set)
{
    struct user_regs_struct regs = {0};

    while (1) {
        if (read_instruction(pid, set, &regs) < 0)
            return -1;
    }
    return 0;
}

int ftrace(pid_t pid, struct settings *set)
{
    if (waitpid(pid, NULL, 0) < 0)
        return 84;
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
    if (read_instructions(pid, set) < 0)
        return -1;
    return 0;
}
