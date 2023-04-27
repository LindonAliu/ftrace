/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "stdio.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_signal(int status)
{
    int signal_number;

    if (!WIFSTOPPED(status))
        return;
    signal_number = WSTOPSIG(status);
    if (signal_number == SIGTRAP)
        return;
    PRINT("Received signal SIG%s\n", sigabbrev_np(signal_number));
}
