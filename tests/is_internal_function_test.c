/*
** EPITECH PROJECT, 2023
** is_internal_function_test
** File description:
** FreeKOSOVO
*/

#include <criterion/criterion.h>

bool is_internal_function(long long res);

Test(is_internal_function, test_e8_opcode)
{
    char bytes[8] = { 0xe8, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00 };
    bool result = is_internal_function(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_internal_function, test_9a_opcode)
{
    char bytes[8] = { 0x9a, 0xaa, 0xbb, 0xcc, 0xdd, 0x00, 0x00, 0x00 };
    bool result = is_internal_function(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_internal_function, test_ff_opcode)
{
    char bytes[8] = { 0xff, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_internal_function(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_internal_function, test_invalid_opcode)
{
    long long res = 0x123456789;
    bool result = is_internal_function(res);
    cr_assert_eq(result, false);
}
