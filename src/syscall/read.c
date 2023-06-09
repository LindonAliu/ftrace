/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "handlers.h"
#include "ftrace.h"
#include "stdio.h"

#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdlib.h>

static void fill_struct(struct syscall_instance *inst,
    struct user_regs_struct *source)
{
    inst->nbr = source->rax;
    inst->args[0] = source->rdi;
    inst->args[1] = source->rsi;
    inst->args[2] = source->rdx;
    inst->args[3] = source->r10;
    inst->args[4] = source->r8;
    inst->args[5] = source->r9;
}

bool is_syscall(long long res)
{
    return ((res & 0xff) == 0x0f) && (((res >> 8) & 0xff) == 0x05);
}

int handle_syscall(pid_t pid, struct user_regs_struct *regs,
    UNUSED struct function_name_stack *func_name_s, struct settings *set)
{
    struct syscall_instance inst = { .pid = pid };

    fill_struct(&inst, regs);
    print_syscall(&inst, set);
    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return PRINT(") = ?\n"), 0;
    print_ret(regs->rax, &inst, set);
    return 0;
}
