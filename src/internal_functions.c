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

int handle_internal_function(pid_t pid, struct user_regs_struct *regs)
{
    char *filepath_ptr = NULL;
    long address_ptr;
    char *function_name = NULL;
    char *filename = NULL;

    if (next_instruction(pid) < 0)
        return -1;
    if (ptrace(PTRACE_GETREGS, pid, NULL, regs) < 0) {
        perror("handle_internal_function ptrace error");
        return -1;
    }
    get_proc_info(&filepath_ptr, &address_ptr, pid, regs->rip);
    function_name = get_symbol_name(filepath_ptr, regs->rip);
    filename = &strrchr(filepath_ptr, '/')[1];
    if (!function_name)
        asprintf(&function_name, "func_%llx@%s", regs->rip, filename);
    PRINT("Entering function %s at 0x%llx\n", function_name, regs->rip);
    free(filepath_ptr);
    free(function_name);
    return 0;
}
