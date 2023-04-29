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
    SLIST_ENTRY(function_names) entries;
};

struct function_name_stack {
    struct function_names *slh_first;
    size_t count;
};
