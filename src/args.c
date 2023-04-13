/*
** EPITECH PROJECT, 2023
** strace
** File description:
** print args
*/

#include "stdio.h"
#include "strace.h"
#include "syscall.h"
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/stat.h>

static void print_string_word(char *str)
{
    for (int i = 0; i < 8; i++) {
        if (str[i] == 0)
            return PRINT("\"");
        if (isprint(str[i]))
            PRINT("%c", str[i]);
        else
            PRINT("\\x%02hhx", str[i]);
    }
}

static void print_string(uint64_t ptr, pid_t pid)
{
    long word;
    char *str = (char *) &word;
    int shift = 0;

    PRINT("\"");
    while (shift < 48) {
        errno = 0;
        word = ptrace(PTRACE_PEEKDATA, pid, ptr + shift, NULL);
        if (errno)
            return PRINT("\" (%s)", strerror(errno));
        print_string_word(str);
        shift += 8;
    }
    return PRINT("\"...");
}

static char *get_mode_filetype_str(mode_t mode)
{
    switch (mode & S_IFMT) {
    case S_IFSOCK: return "S_IFSOCK";
    case S_IFLNK: return "S_IFLNK";
    case S_IFREG: return "S_IFREG";
    case S_IFBLK: return "S_IFBLK";
    case S_IFDIR: return "S_IFDIR";
    case S_IFCHR: return "S_IFCHR";
    case S_IFIFO: return "S_IFIFO";
    }
    return "S_IF?";
}

static void print_stat(uint64_t ptr, pid_t pid)
{
    long word;
    struct stat loaded = {};

    for (unsigned i = 0; i * 8 < sizeof(struct stat) && !errno; i++) {
        errno = 0;
        word = ptrace(PTRACE_PEEKDATA, pid, ptr + i * 8, NULL);
        ((long *) &loaded)[i] = word;
    }
    PRINT("{st_mode=%s|0%o, st_size=%lu, ...}",
        get_mode_filetype_str(loaded.st_mode),
        loaded.st_mode & 0777, loaded.st_size);
}

void print_arg(uint64_t value, enum syscall_type type,
    struct settings *set, pid_t pid)
{
    if (!set->pretty_args)
        return PRINT("0x%lx", value);
    if (type == VOID)
        return;
    if (type == VOID_P || type == PVOID || type == CONST_VOID_P)
        return PRINT(value ? "0x%lx" : "NULL", value);
    if (type == NUM)
        return PRINT("%ld", value);
    if (type == UNSIGNED)
        return PRINT("%lu", value);
    if (type == STRING)
        return print_string(value, pid);
    if (type == STRUCT_STAT_P)
        return print_stat(value, pid);
    PRINT("0x%lx", value);
}
