/*
** EPITECH PROJECT, 2023
** is_syscall_test
** File description:
** FreeKOSOVO
*/

#include <criterion/criterion.h>
#include <stdbool.h>

bool is_syscall(long long res);

Test(is_syscall, test_valid_syscall)
{
    char bytes[8] = { 0x0f, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_syscall(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_syscall, test_first_byte_is_invalid)
{
    char bytes[8] = { 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff };
    bool result = is_syscall(*(long long *) bytes);
    cr_assert_eq(result, false);
}

Test(is_syscall, test_second_byte_is_invalid)
{
    char bytes[8] = { 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff };
    bool result = is_syscall(*(long long *) bytes);
    cr_assert_eq(result, false);
}

Test(is_syscall, test_all_bytes_are_invalid)
{
    char bytes[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff };
    bool result = is_syscall(*(long long *) bytes);
    cr_assert_eq(result, false);
}
