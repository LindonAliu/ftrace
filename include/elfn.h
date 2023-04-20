/*
** EPITECH PROJECT, 2023
** nm/objdump
** File description:
** elf macros
*/

#pragma once

#include <elf.h>

#define EH64 ((Elf64_Ehdr *) doc->elf)
#define EH32 ((Elf32_Ehdr *) doc->elf)
#define EH_IS_64 (EH64->e_ident[EI_CLASS] == ELFCLASS64)
#define EH(m) (EH_IS_64 ? EH64->m : EH32->m)

#define SH_ (doc->elf + EH(e_shoff))
#define SH(a, b) (EH_IS_64 ? a((Elf64_Shdr *) SH_)b : a((Elf32_Shdr *) SH_)b)
#define SH_SIZE (EH_IS_64 ? sizeof(Elf64_Shdr) : sizeof(Elf32_Shdr))

#define SYM64 ((Elf64_Sym *) sym)
#define SYM32 ((Elf32_Sym *) sym)
#define SYM(m) (EH_IS_64 ? SYM64->m : SYM32->m)
#define SYM_SIZE (EH_IS_64 ? sizeof(Elf64_Sym) : sizeof(Elf32_Sym))
