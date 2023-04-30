/*
** EPITECH PROJECT, 2023
** is_tail_call_test
** File description:
** FreeKOSOVO
*/

#include <criterion/criterion.h>
#include <stdbool.h>

#include <criterion/criterion.h>
#include <stdbool.h>

bool is_tail_call(long long res);

Test(is_tail_call, test_e9_opcode)
{
    char bytes[8] = { 0xe9, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_tail_call, test_eb_opcode)
{
    char bytes[8] = { 0xeb, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_tail_call, test_ff_opcode_with_offset_2)
{
    char bytes[8] = { 0xff, 0xe4, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_tail_call, test_ff_opcode_with_offset_3)
{
    char bytes[8] = { 0xff, 0xe5, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_tail_call, test_invalid_opcode)
{
    char bytes[8] = { 0x90, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, false);
}
