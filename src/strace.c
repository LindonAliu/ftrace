/*
** EPITECH PROJECT, 2023
** strace
** File description:
** FreeKOSOVO
*/

#include "strace.h"
#include "stdio.h"

#include <sys/ptrace.h>
#include <sys/user.h>
#include <stddef.h>
#include <sys/wait.h>

void fill_struct(struct syscall_instance *inst, struct user_regs_struct source)
{
    inst->nbr = source.rax;
    inst->args[0] = source.rdi;
    inst->args[1] = source.rsi;
    inst->args[2] = source.rdx;
    inst->args[3] = source.r10;
    inst->args[4] = source.r8;
    inst->args[5] = source.r9;
}

static int next_instruction(pid_t pid)
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

int read_instructions(pid_t pid, struct settings *set)
{
    struct user_regs_struct regs = {0};
    struct syscall_instance inst = { .pid = pid };

    while (1) {
        if (next_instruction(pid) < 0)
            break;
        if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) < 0)
            return -1;
        if (!is_syscall(pid, &regs))
            continue;
        fill_struct(&inst, regs);
        print_syscall(&inst, set);
        if (next_instruction(pid) < 0)
            break;
        if (ptrace(PTRACE_GETREGS, pid, NULL, &regs) < 0)
            return PRINT(") = ?\n"), 0;
        print_ret(regs.rax, &inst, set);
    }
    return 0;
}

int strace(pid_t pid, struct settings *set)
{
    if (waitpid(pid, NULL, 0) < 0)
        return 84;
    ptrace(PTRACE_SETOPTIONS, pid, NULL, PTRACE_O_TRACESYSGOOD);
    if (read_instructions(pid, set) < 0)
        return -1;
    return 0;
}
