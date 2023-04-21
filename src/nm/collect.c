/*
** EPITECH PROJECT, 2023
** nm
** File description:
** collect symbols
*/

#include "nm.h"
#include "elfn.h"

#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned find_section(struct document *doc, uint32_t type)
{
    for (unsigned i = 0; i < EH(e_shnum); i++) {
        if (EH(e_shoff) + i + SH_SIZE > doc->length)
            return 0;
        if (SH(, [i].sh_type) == type)
            return i;
    }
    return 0;
}

static bool fill_symbol(
    void *sym, struct symbol *symbol, char *strtab, struct document *doc)
{
    if (SYM(st_name) == 0)
        return false;
    symbol->name = strtab + SYM(st_name);
    symbol->value = SYM(st_value);
    if (ELF64_ST_TYPE(SYM(st_info)) == STT_FILE)
        return false;
    return true;
}

struct symbol *collect_symbols(struct document *doc)
{
    unsigned sec_idx = find_section(doc, SHT_SYMTAB);
    void *sym;
    unsigned symbol_count;
    struct symbol *res;
    unsigned si = 0;

    if (sec_idx == 0)
        return NULL;
    sym = doc->elf + SH(, [sec_idx].sh_offset);
    symbol_count = SH(, [sec_idx].sh_size) / SH(, [sec_idx].sh_entsize);
    res = malloc(sizeof(struct symbol[symbol_count + 1]));
    for (unsigned i = 0; i < symbol_count; i++) {
        si += fill_symbol(
            sym + i * SYM_SIZE, &res[si],
            doc->elf + SH(, [SH(, [sec_idx].sh_link)].sh_offset), doc);
    }
    res[si].name = NULL;
    return res;
}
