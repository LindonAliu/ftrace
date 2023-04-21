/*
** EPITECH PROJECT, 2023
** nm
** File description:
** header
*/

#pragma once

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

struct document {
    void *elf;
    size_t length;
    char *filepath;
};

struct symbol {
    size_t value;
    char *name;
};

struct symbol *collect_symbols(struct document *doc);
char *get_symbol_name(char *filepath, long address);
