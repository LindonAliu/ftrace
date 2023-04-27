/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "stdio.h"
#include "nm.h"
#include "stack.h"

#include <stddef.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/queue.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <stdlib.h>

bool is_internal_function(pid_t pid, struct user_regs_struct *regs)
{
    long long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    if ((res & 0xff) == 0xe8 || (res & 0xff) == 0x9a)
        return true;
    if ((res & 0xff) == 0xff && ((res >> (8 + 4)) & 0b11) == 0b01)
        return true;
    return false;
}

static char *base_filename(char *filepath)
{
    char *filename = strrchr(filepath, '/');

    if (filename != NULL)
        filename += 1;
    else
        filename = filepath;
    return filename;
}

static int insert_into_stack(char *function_name,
    struct function_name_stack *func_name_s)
{
    struct function_names *fn_s;

    fn_s = malloc(sizeof(struct function_names));
    if (fn_s == NULL)
        return -1;
    fn_s->name = function_name;
    SLIST_INSERT_HEAD(func_name_s, fn_s, entries);
    return 0;
}

int handle_internal_function(pid_t pid, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s)
{
    long address;
    char *filepath = NULL;
    char *function_name = NULL;
    char *filename = NULL;

    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return -1;
    get_proc_info(&filepath, &address, pid, regs->rip);
    function_name = get_symbol_name(filepath, regs->rip, &address);
    filename = base_filename(filepath);
    if (!function_name)
        asprintf(&function_name, "func_%lx@%s", address, filename);
    PRINT("Entering function %s at 0x%llx\n", function_name, regs->rip);
    insert_into_stack(function_name, func_name_s);
    free(filepath);
    return 0;
}
