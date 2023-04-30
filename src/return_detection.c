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

bool is_return(long long res)
{
    res &= 0xff;
    if (res == 0xc3 || res == 0xcb)
        return 1;
    return 0;
}

static void pop_stack(struct function_name_stack *func_name_s,
    struct settings *set, char const *info)
{
    struct function_names *fn_s = SLIST_FIRST(func_name_s);

    if (fn_s == NULL)
        return;
    SLIST_REMOVE_HEAD(func_name_s, entries);
    func_name_s->count--;
    IPRINT("Leaving function %s%s\n", fn_s->name, info);
    free(fn_s->name);
    free(fn_s);
}

static void fix_stack(struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, struct settings *set)
{
    struct function_names *fn_s = SLIST_FIRST(func_name_s);

    while (fn_s != NULL && regs->rsp > fn_s->rsp) {
        pop_stack(func_name_s, set, " (Skipped)");
        fn_s = SLIST_FIRST(func_name_s);
    }
    if (fn_s == NULL)
        return;
    if (regs->rsp < fn_s->rsp) {
        IPRINT("Leaving function (No corresponding call at rsp %llu)\n",
            regs->rsp);
        return;
    }
    pop_stack(func_name_s, set, "");
}

int handle_return(pid_t pid, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, struct settings *set)
{
    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return -1;
    fix_stack(regs, func_name_s, set);
    return 0;
}
