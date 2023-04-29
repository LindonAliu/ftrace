/*
** EPITECH PROJECT, 2023
** stdio
** File description:
** FreeKOSOVO
*/

#pragma once

#include <stdio.h>

#define PRINT(...) (void) fprintf(stderr, __VA_ARGS__)
#define IPRINT_IMPL(fmt, ...) (void) fprintf(stderr, "%*s" fmt, \
    (int) (func_name_s->count), "", __VA_ARGS__)

#define IPRINT(...) (set->indent ? IPRINT_IMPL(__VA_ARGS__) : PRINT\
    (__VA_ARGS__))
