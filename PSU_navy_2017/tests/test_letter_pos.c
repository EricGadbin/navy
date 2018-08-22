/*
** EPITECH PROJECT, 2018
** Project navy Testing
** File description:
** Unit Testing Project navy
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <ctype.h>
#include "main.h"

Test(navy, pos_letter_no_loop)
{
	cr_assert_eq(get_pos_from_letter('A'), 2);
}

Test(navy, pos_letter)
{
	cr_assert_eq(get_pos_from_letter('F'), 12);
}

Test(navy, pos_letter_error)
{
	cr_assert_eq(get_pos_from_letter('T'), 84);
}
