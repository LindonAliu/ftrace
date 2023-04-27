/*
** EPITECH PROJECT, 2023
** proc
** File description:
** FreeKOSOVO
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *get_proc_filepath(pid_t pid)
{
    char *proc_filepath = NULL;

    asprintf(&proc_filepath, "/proc/%d/maps", pid);
    return proc_filepath;
}

static int fill_proc_info(char **filepath_ptr, long *address_ptr,
    char *line_read, long address)
{
    long first_address = 0;
    long last_address = 0;
    char *shift;

    first_address = strtol(line_read, NULL, 16);
    last_address = strtol(strchr(line_read, '-') + 1, &shift, 16);
    if (first_address <= address && address < last_address) {
        line_read[strlen(line_read) - 1] = '\0';
        *filepath_ptr = strdup(strrchr(line_read, ' ') + 1);
        *address_ptr = first_address - strtol(strchr(shift + 1, ' ') + 1,
            NULL, 16);
        return 0;
    }
    return -1;
}

void get_proc_info(char **filepath_ptr, long *address_ptr,
    pid_t pid, long address)
{
    char *proc_filepath = get_proc_filepath(pid);
    FILE *f = fopen(proc_filepath, "r");
    char *line_read = NULL;
    size_t size = 0;

    free(proc_filepath);
    if (f == NULL)
        return;
    while (getline(&line_read, &size, f) > 0 &&
        fill_proc_info(filepath_ptr, address_ptr, line_read, address) == -1);
    free(line_read);
    fclose(f);
}
