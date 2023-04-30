/*
** EPITECH PROJECT, 2023
** is_return_test
** File description:
** FreeKOSOVO
*/

#include <criterion/criterion.h>
#include <stdbool.h>

bool is_return(long long res);

Test(is_return, test_is_return_true)
{
    char bytes[8] = { 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff };
    bool result = is_return(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_return, test_is_return_true2)
{
    char bytes[8] = { 0xcb, 0x00, 0x00, 0x00, 0xc3, 0x00, 0xff, 0xff };
    bool result = is_return(*(long long *) bytes);
    cr_assert_eq(result, true);
}

Test(is_return, test_is_return_false)
{
    char bytes[8] = { 0x00, 0x00, 0x00, 0x00, 0x00 };
    bool result = is_return(*(long long *) bytes);
    cr_assert_eq(result, false);
}
