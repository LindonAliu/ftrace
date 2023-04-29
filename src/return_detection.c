/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "stdio.h"
#include "ftrace.h"
#include "handlers.h"

#include <sys/queue.h>
#include <sys/user.h>
#include <sys/ptrace.h>
#include <stdlib.h>

bool is_return(pid_t pid, struct user_regs_struct *regs)
{
    long long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    res &= 0xff;
    if (res == 0xc3 || res == 0xcb)
        return 1;
    return 0;
}

int handle_return(pid_t pid, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, UNUSED struct settings *set)
{
    struct function_names *fn_s = SLIST_FIRST(func_name_s);

    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return -1;
    if (fn_s == NULL)
        return 0;
    SLIST_REMOVE_HEAD(func_name_s, entries);
    func_name_s->count--;
    IPRINT("Leaving function %s\n", fn_s->name);
    free(fn_s->name);
    free(fn_s);
    return 0;
}
