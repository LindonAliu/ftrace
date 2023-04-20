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
    char *proc_filepath = NULL;
    FILE *f = NULL;
    char *line_read = NULL;
    ssize_t size = 0;
    long first_adress = 0;
    long last_adress = 0;
    void *end_ptr = NULL;

    asprintf(&proc_filepath, "/proc/%d/maps", pid);    
    f = fopen(proc_filepath, "r");
    if (f == NULL)
        return;
    while (getline(&line_read, &size, f) > 0) {
        printf("%s", line_read);
        line_read[strlen(line_read) - 1] = '\0';
        first_adress = strtol(line_read, &end_ptr, 16);
        last_adress = strtol(end_ptr + 1, &end_ptr, 16);
        if (first_adress <= adress && adress < last_adress) {
            end_ptr = strrchr(line_read, ' ');
            *filepath_ptr = strdup(end_ptr + 1);
            *adress_ptr = adress;
            break;
        }
    }
    free(line_read);
    fclose(f);
}

int main(void)
{
    char *filepath = NULL;
    long adress = 0;

    get_proc_info(&filepath, &adress, getpid(), (long)main);
    printf("filepath: %s adress: %lx\n", filepath, adress);
}