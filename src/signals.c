/*
** EPITECH PROJECT, 2023
** read
** File description:
** FreeKOSOVO
*/

#include "stdio.h"
#include "handlers.h"

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_signal(int status)
{
    int signals[] = { SIGSEGV, SIGFPE, SIGBUS, SIGILL };
    int signal_number;

    if (!WIFSTOPPED(status))
        return;
    signal_number = WSTOPSIG(status);
    if (signal_number == SIGTRAP)
        return;
    PRINT("Received signal SIG%s\n", sigabbrev_np(signal_number));
    for (size_t i = 0; i < SIZE_ARRAY(signals); i++) {
        if (signal_number == signals[i])
            exit(128 + signal_number);
    }
}
