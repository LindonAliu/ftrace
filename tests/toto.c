/*
** EPITECH PROJECT, 2023
** toto
** File description:
** FreeKOSOVO
*/

#include <unistd.h>

int my_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return i;
}

void my_putstr(char *str)
{
    write(1, str, my_strlen(str));
}

void toto(void)
{
    my_putstr("i am in toto()\n");
}

void tutu(void)
{
    my_putstr("i am in tutu()\n");
}

int main(void)
{
    toto();
    tutu();
}
