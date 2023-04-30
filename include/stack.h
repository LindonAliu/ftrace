/*
** EPITECH PROJECT, 2023
** nm
** File description:
** header
*/

#pragma once

#include <stddef.h>
#include <sys/queue.h>

struct function_names {
    char *name;
    unsigned long long rsp;
    SLIST_ENTRY(function_names) entries;
};

struct function_name_stack {
    struct function_names *slh_first;
    size_t count;
};

int insert_into_stack(
    char *function_name, unsigned long long rsp,
    struct function_name_stack *func_name_s);
