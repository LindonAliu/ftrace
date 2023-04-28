/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "nm.h"
#include "stack.h"
#include "stdio.h"
#include "handlers.h"

#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/queue.h>
#include <sys/user.h>
#include <stddef.h>
#include <sys/wait.h>

int next_instruction(pid_t pid)
{
    int process_status;

    if (ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL) < 0)
        return -1;
    if (waitpid(pid, &process_status, 0) < 0)
        return -1;
    display_signal(process_status);
    return 0;
}

static int read_instruction(pid_t pid, struct settings *set,
    struct user_regs_struct *regs, struct function_name_stack *func_name_s)
{
    for (size_t i = 0; i < SIZE_ARRAY(READINGS); i++) {
        if (READINGS[i].is_tracable(pid, regs))
            return READINGS[i].handle(pid, regs, func_name_s, set);
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
    struct function_name_stack function_name_s;
    struct function_names *fn;

    SLIST_INIT(&function_name_s);
    while (1) {
        if (read_instruction(pid, set, &regs, &function_name_s) < 0)
            return -1;
    }
    while (!SLIST_EMPTY(&function_name_s)) {
        fn = SLIST_FIRST(&function_name_s);
        SLIST_REMOVE_HEAD(&function_name_s, entries);
        free(fn->name);
        free(fn);
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
