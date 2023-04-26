/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** header
*/

#pragma once

#include <inttypes.h>
#include <stdbool.h>
#include <sys/types.h>

struct syscall_instance {
    /// The PID of the traced process
    pid_t pid;
    /// The syscall number
    int nbr;
    /// The arguments given
    uint64_t args[6];
    /// The number of printed
    int printed_arg_count;
};

struct settings {
    bool pretty_args;
};

int next_instruction(pid_t pid);

struct user_regs_struct;
int handle_syscall(struct user_regs_struct *regs,
    pid_t pid, struct settings *set);
void print_syscall(struct syscall_instance *instance, struct settings *set);

enum syscall_type;
void print_arg(uint64_t value, enum syscall_type type,
    struct settings *set, pid_t pid);
void print_ret(uint64_t value, struct syscall_instance *instance,
    struct settings *set);

/**
 * @brief Get the filepath of the object file and the address of the function
 *
 * @param filepath_ptr The address of the string to set the filepath
 * @param address_ptr  The address of the ptr to set the address of the function
 * @param pid The pid of the process
 * @param address The address to search
 */
void get_proc_info(char **filepath_ptr, long *address_ptr,
    pid_t pid, long address);

int ftrace(pid_t pid, struct settings *set, int ac, const char *av[]);

int is_internal_function(pid_t pid, struct user_regs_struct *regs);
int handle_internal_function(pid_t pid, struct user_regs_struct *regs,
    int ac, const char *av[]);
