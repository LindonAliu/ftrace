/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** header
*/

#pragma once

#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <sys/types.h>

struct user_regs_struct;
enum syscall_type;

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
    bool indent;
};

int next_instruction(pid_t pid);

void print_syscall(struct syscall_instance *instance, struct settings *set);
void print_arg(uint64_t value, enum syscall_type type,
    struct settings *set, pid_t pid);
void print_ret(uint64_t value, struct syscall_instance *instance,
    struct settings *set);

void display_signal(int status);

void get_proc_info(char **filepath_ptr, long *address_ptr,
    pid_t pid, long address);

int ftrace(pid_t pid, struct settings *set);

int parse_options(int ac, char *av[], struct settings *s);
