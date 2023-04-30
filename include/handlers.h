/*
** EPITECH PROJECT, 2023
** handlers
** File description:
** FreeKOSOVO
*/

#pragma once

#include <stdbool.h>
#include <sys/types.h>

#define SIZE_ARRAY(array) (sizeof(array) / sizeof(*array))
#define UNUSED __attribute__((unused))

struct user_regs_struct;
enum syscall_type;
struct function_name_stack;
struct settings;

typedef bool is_tracable_t(long long res);
typedef int handle_t(pid_t pid, struct user_regs_struct *regs,
    struct function_name_stack *func_name_s, struct settings *set);

is_tracable_t is_syscall;
is_tracable_t is_internal_function;
is_tracable_t is_return;
is_tracable_t is_tail_call;

handle_t handle_syscall;
handle_t handle_internal_function;
handle_t handle_return;
handle_t handle_tail_call;

struct reading {
    is_tracable_t *is_tracable;
    handle_t *handle;
};

static const struct reading READINGS[] = {
    {&is_syscall, &handle_syscall},
    {&is_internal_function, &handle_internal_function},
    {&is_return, &handle_return},
    {&is_tail_call, &handle_tail_call},
};
