/*
** EPITECH PROJECT, 2023
** options
** File description:
** FreeKOSOVO
*/

#include "ftrace.h"
#include "stdio.h"
#include <string.h>

static void parse_option(char opt, struct settings *s)
{
    switch (opt) {
    case 's':
        s->pretty_args = true;
        break;
    case 'i':
        s->indent = true;
        break;
    case 'a':
        s->function_args = true;
        break;
    default:
        PRINT("Ignoring invalid option: %c\n", opt);
    }
}

int parse_options(int ac, char *av[], struct settings *s)
{
    int i = 1;

    if (ac == 3 && strcmp(av[1], "-p") == 0)
        return 1;
    while (i < ac) {
        if (av[i][0] != '-')
            break;
        for (int j = 1; av[i][j] != '\0'; j++) {
            parse_option(av[i][j], s);
        }
        i++;
    }
    return i;
}
