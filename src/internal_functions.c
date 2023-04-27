/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "stdio.h"
#include "nm.h"

#include <stddef.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <stdlib.h>

int is_internal_function(pid_t pid, struct user_regs_struct *regs)
{
    long long res = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, NULL);

    res &= 0xff;
    if (res == 0xe8 || res == 0xff || res == 0x9a)
        return 1;
    return 0;
}

static char *base_filename(char *filepath_ptr)
{
    char *filename = strrchr(filepath_ptr, '/');

    if (filename)
        filename += 1;
    else
        filename = filepath_ptr;
    return filename;
}

int handle_internal_function(pid_t pid, struct user_regs_struct *regs)
{
    char *filepath = NULL;
    long address;
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
    free(filepath);
    free(function_name);
    return 0;
}
