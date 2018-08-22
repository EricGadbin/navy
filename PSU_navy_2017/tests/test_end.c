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
int check_map(char character);

Test(navy, test_check_map_true)
{
	cr_assert_eq(check_map('x'), 1);
}

Test(navy, test_check_map_false)
{
	cr_assert_eq(check_map('b'), 0);
}

Test(navy, test_game_not_over)
{
	global_t *global = malloc(sizeof(*global));

	global->boat_map = load_map("tests/pos1");
	global->map = create_empty_map(global->map);
	cr_assert_eq(check_end_game(global), 2);
	free_map(global->boat_map);
	free_map(global->map);
	free(global);
}

Test(navy, test_game_won)
{
	global_t *global = malloc(sizeof(*global));

	global->boat_map = load_map("tests/pos1");
	global->map = create_empty_map(global->map);
	for (int i = 2; i < 13; i += 2) {
		for (int j = 2; j < 4; j++)
			global->map[j][i] = 'x';
	}
	global->map[4][2] = 'x';
	global->map[4][4] = 'x';
	cr_assert_eq(check_end_game(global), 0);
	free_map(global->boat_map);
	free_map(global->map);
	free(global);
}

Test(navy, test_game_lost)
{
	global_t *global = malloc(sizeof(*global));

	global->boat_map = create_empty_map(global->boat_map);
	global->map = create_empty_map(global->map);
	for (int i = 2; i < 13; i += 2) {
		for (int j = 2; j < 4; j++)
			global->boat_map[j][i] = 'x';
	}
	global->boat_map[4][2] = 'x';
	global->boat_map[4][4] = 'x';
	cr_assert_eq(check_end_game(global), 1);
	free_map(global->boat_map);
	free_map(global->map);
	free(global);
}
