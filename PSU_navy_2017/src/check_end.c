/*
** EPITECH PROJECT, 2018
** check_end.c
** File description:
** navy
*/

#include "main.h"

int check_map(char character)
{
	int count = 0;

	if (character == 'x')
		count = 1;
	return (count);
}

int check_end_game(global_t *global)
{
	int count_p = 0;
	int count_e = 0;

	for (int line = 2; line < 10; line += 1) {
		for (int col = 2; col < 17; col += 2) {
			count_p += check_map(global->boat_map[line][col]);
			count_e += check_map(global->map[line][col]);
		}
	}
	if (count_e == 14) {
		display(global);
		my_printf("I won\n\n");
		return (0);
	} else if (count_p == 14) {
		display(global);
		my_printf("Enemy won\n\n");
		return (1);
	}
	return (2);
}
