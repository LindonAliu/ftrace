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

static int fill_proc_info(char **filepath_ptr, long *adress_ptr,
    char *line_read, long adress)
{
    long first_adress = 0;
    long last_adress = 0;

    first_adress = strtol(line_read, NULL, 16);
    last_adress = strtol(strchr(line_read, '-') + 1, NULL, 16);
    if (first_adress <= adress && adress < last_adress) {
        line_read[strlen(line_read) - 1] = '\0';
        *filepath_ptr = strdup(strrchr(line_read, ' ') + 1);
        *adress_ptr = adress;
        return 0;
    }
    return -1;
}

/**
 * @brief Get the filepath of the object file and the adress of the function
 *
 * @param filepath_ptr The adress of the string to set the filepath
 * @param adress_ptr  The adress of the ptr to set the adress of the function
 * @param pid The pid of the process
 * @param adress The adress to search
 */
void get_proc_info(char **filepath_ptr, long *adress_ptr,
    pid_t pid, long adress)
{
    char *proc_filepath = get_proc_filepath(pid);
    FILE *f = fopen(proc_filepath, "r");
    char *line_read = NULL;
    size_t size = 0;

    free(proc_filepath);
    if (f == NULL)
        return;
    while (getline(&line_read, &size, f) > 0) {
        if (fill_proc_info(filepath_ptr, adress_ptr, line_read, adress) == 0)
            break;
    }
    free(line_read);
    fclose(f);
}
