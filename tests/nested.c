/*
** EPITECH PROJECT, 2023
** ftrace tests
** File description:
** nested function
*/

#include <stdio.h>

void call_and_print(int (*f)(void))
{
    printf("%d\n", f());
}

int main(int ac, char *av[])
{
    int local()
    {
        return ac;
    };
    call_and_print(local);
}
