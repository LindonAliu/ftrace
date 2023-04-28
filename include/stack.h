/*
** EPITECH PROJECT, 2023
** nm
** File description:
** header
*/

#pragma once

#include <sys/queue.h>

struct function_names {
    char *name;
    SLIST_ENTRY(function_names) entries;
};

SLIST_HEAD(function_name_stack, function_names);
