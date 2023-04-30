/*
** EPITECH PROJECT, 2023
** is_tail_call_test
** File description:
** FreeKOSOVO
*/

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

Test(is_tail_call, test_ff_slash_4)
{
    char bytes[8] = { 0xff, 0b00100000, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_tail_call, test_ff_slash_5)
{
    char bytes[8] = { 0xff, 0b00101000, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_tail_call, test_ff_slash_1)
{
    char bytes[8] = { 0xff, 0b00001000, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, false);
}

Test(is_tail_call, test_ff_slash_3)
{
    char bytes[8] = { 0xff, 0b00011000, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, false);
}

Test(is_tail_call, test_invalid_opcode)
{
    char bytes[8] = { 0x90, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00 };
    bool result = is_tail_call(*(long long *) bytes);
    cr_assert_eq(result, false);
}
