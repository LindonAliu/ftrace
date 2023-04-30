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
#include "handlers.h"

#include <stddef.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/queue.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <stdlib.h>

bool is_internal_function(long long res)
{
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

int insert_into_stack(char *function_name, unsigned long long rsp,
    struct function_name_stack *func_name_s)
{
    struct function_names *fn_s;

    fn_s = malloc(sizeof(struct function_names));
    if (fn_s == NULL) {
        free(function_name);
        return -1;
    }
    fn_s->name = function_name;
    fn_s->rsp = rsp;
    SLIST_INSERT_HEAD(func_name_s, fn_s, entries);
    func_name_s->count++;
    return 0;
}

static void print_enter(
    char *function_name, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, struct settings *set)
{
    IPRINT("Entering function %s at 0x%llx", function_name, regs->rip);
    if (set->function_args) {
        PRINT(" (%#llx, %#llx, %#llx, %#llx, %#llx, %#llx)",
            regs->rdi, regs->rsi, regs->rdx, regs->rcx, regs->r8, regs->r9);
    }
    PRINT("\n");
}

int handle_internal_function(pid_t pid, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, struct settings *set)
{
    long address;
    char *filepath = NULL;
    char *function_name = NULL;
    char *filename = NULL;
    unsigned long long rsp = regs->rsp;

    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0)
        return -1;
    get_proc_info(&filepath, &address, pid, regs->rip);
    function_name = get_symbol_name(filepath, regs->rip, &address);
    filename = base_filename(filepath);
    if (!function_name)
        asprintf(&function_name, "func_%lx@%s", address, filename);
    print_enter(function_name, regs, func_name_s, set);
    insert_into_stack(function_name, rsp, func_name_s);
    free(filepath);
    return 0;
}
