/*
** EPITECH PROJECT, 2023
** strace
** File description:
** printing
*/

#include "strace.h"
#include "syscall.h"
#include "stdio.h"
#include <string.h>
#include <errno.h>

static struct syscall_entry *get_syscall_entry(long nbr)
{
    static char name[256];
    static struct syscall_entry error = { .name = name, .nb_args = 6 };

    snprintf(name, 256, "syscall_%#lx", nbr);
    if (nbr < 0 || nbr >= MAX_SYSCALL_NB)
        return &error;
    if (!SYSCALL_TABLE[nbr].name)
        return &error;
    return &SYSCALL_TABLE[nbr];
}

void print_syscall(struct syscall_instance *instance, struct settings *set)
{
    struct syscall_entry *entry = get_syscall_entry(instance->nbr);

    PRINT("Syscall %s (", entry->name);
    instance->printed_arg_count = 0;
    while (instance->printed_arg_count < entry->nb_args
        && entry->args[instance->printed_arg_count] != STRUCT_STAT_P) {
        PRINT("%s", instance->printed_arg_count == 0 ? "" : ", ");
        print_arg(
            instance->args[instance->printed_arg_count],
            entry->args[instance->printed_arg_count], set, instance->pid);
        instance->printed_arg_count++;
    }
}

void print_ret(uint64_t value, struct syscall_instance *instance,
    struct settings *set)
{
    struct syscall_entry *entry = get_syscall_entry(instance->nbr);

    while (instance->printed_arg_count < entry->nb_args) {
        PRINT("%s", instance->printed_arg_count == 0 ? "" : ", ");
        print_arg(
            instance->args[instance->printed_arg_count],
            entry->args[instance->printed_arg_count], set, instance->pid);
        instance->printed_arg_count++;
    }
    PRINT(") = ");
    if (value > -4096UL) {
        PRINT("-1 %s (%s)\n", strerrorname_np(-value), strerror(-value));
        return;
    }
    print_arg(value, entry->ret, set,
        instance->pid);
    PRINT("\n");
}
