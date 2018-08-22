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
int structreset(global_t *global);

Test(navy, test_struct_reset_return)
{
	global_t *global = malloc(sizeof(*global));

	cr_assert_eq(structreset(global), 0);
	free(global);
}

Test(navy, test_struct_reset_sig1)
{
	global_t *global = malloc(sizeof(*global));

	global->sig1 = 1;
	structreset(global);
	cr_assert_eq(global->sig1, 0);
	free(global);
}

Test(navy, test_struct_reset_sig2)
{
	global_t *global = malloc(sizeof(*global));

	global->sig2 = 1;
	structreset(global);
	cr_assert_eq(global->sig2, 0);
	free(global);
}
