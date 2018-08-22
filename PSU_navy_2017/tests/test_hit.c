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

Test(navy, test_hit_player_true)
{
	char **map = load_map("tests/pos1");

	cr_assert_eq(check_if_player_was_hit(map, 1, 1), 1);
	free_map(map);
}

Test(navy, test_hit_player_fasle)
{
	char **map = load_map("tests/pos1");

	cr_assert_eq(check_if_player_was_hit(map, 2, 1), 0);
	free_map(map);
}
