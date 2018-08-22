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
char *fill_normal_lines(char *line);
char *fill_second_line(char *line);
char *fill_first_line(char *line);

Test(navy, test_fill_first_line)
{
	char *str = NULL;

	cr_assert_str_eq(fill_first_line(str), " |A B C D E F G H");
}

Test(navy, test_fill_secnd_line)
{
	char *str = NULL;

	cr_assert_str_eq(fill_second_line(str), "-+---------------");
}

Test(navy, test_fill_normal_line)
{
	char *str = NULL;

	cr_assert_str_eq(fill_normal_lines(str), "1|. . . . . . . .");
}
