/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** Support for tail calls
*/

#include "ftrace.h"
#include "stdio.h"
#include "nm.h"
#include "stack.h"
#include "handlers.h"

#include <sys/ptrace.h>
#include <sys/queue.h>
#include <sys/user.h>
#include <stdlib.h>

/// Detect E9, EB, FF /4, FF /5
bool is_tail_call(pid_t pid, struct user_regs_struct *regs)
{
    long long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    if ((res & 0xff) == 0xe9 || (res & 0xff) == 0xeb)
        return true;
    if ((res & 0xff) == 0xff && ((res >> (8 + 4)) & 0b11) == 0b10)
        return true;
    return false;
}

static int replace_in_stack(char *function_name,
    struct function_name_stack *func_name_s)
{
    struct function_names *fn_s = SLIST_FIRST(func_name_s);

    if (fn_s == NULL) {
        free(function_name);
        return -1;
    }
    fn_s->name = function_name;
    return 0;
}

int handle_tail_call(pid_t pid, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, struct settings *set UNUSED)
{
    long address;
    char *filepath = NULL;
    char *function_name = NULL;

    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return -1;
    get_proc_info(&filepath, &address, pid, regs->rip);
    function_name = get_symbol_name(filepath, regs->rip, &address);
    if (!function_name) {
        free(filepath);
        return 0;
    }
    PRINT("Entering function %s at 0x%llx (Tail call)\n",
        function_name, regs->rip);
    replace_in_stack(function_name, func_name_s);
    free(filepath);
    return 0;
}
