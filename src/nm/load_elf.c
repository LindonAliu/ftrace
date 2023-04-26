/*
** EPITECH PROJECT, 2023
** nm/objdump
** File description:
** load elf file
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>

#include "nm.h"
#include "elfn.h"

void *load_elf(char *name, size_t *length)
{
    int fd = open(name, O_RDONLY);
    struct stat s;
    void *res;

    if (fd == -1)
        return NULL;
    fstat(fd, &s);
    *length = s.st_size;
    res = mmap(NULL, s.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return res == MAP_FAILED ? NULL : res;
}

Elf64_Ehdr *check_elf_header(void *_doc, size_t length)
{
    struct document idoc = { .elf = _doc, .length = length};
    struct document *doc = &idoc;

    if (length < sizeof(Elf64_Ehdr)
        || EH(e_ident[EI_MAG0]) != ELFMAG0
        || EH(e_ident[EI_MAG1]) != ELFMAG1
        || EH(e_ident[EI_MAG2]) != ELFMAG2
        || EH(e_ident[EI_MAG3]) != ELFMAG3
        || EH(e_ident[EI_VERSION]) != EV_CURRENT
        || EH(e_version) != EV_CURRENT
        || length < EH(e_shoff) + EH(e_shentsize) * EH(e_shnum))
        return NULL;
    return _doc;
}

static char *get_symbol_at(struct document *doc, size_t address)
{
    struct symbol *symbols = collect_symbols(doc);
    char *ret = NULL;

    if (symbols == NULL)
        return NULL;
    for (unsigned i = 0; symbols[i].name; i++) {
        if (address == symbols[i].value) {
            ret = strdup(symbols[i].name);
            break;
        }
    }
    free(symbols);
    return ret;
}

char *get_symbol_name(char *filepath, long address)
{
    struct document doc;
    void *_elf = load_elf(filepath, &doc.length);
    char *ret;

    if (_elf == NULL)
        return NULL;
    doc.filepath = filepath;
    doc.elf = _elf;
    if (!check_elf_header(_elf, doc.length)) {
        munmap(_elf, doc.length);
        return NULL;
    }
    ret = get_symbol_at(&doc, address);
    munmap(_elf, doc.length);
    return ret;
}
