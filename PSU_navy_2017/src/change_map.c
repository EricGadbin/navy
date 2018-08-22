/*
** EPITECH PROJECT, 2018
** change_map.c
** File description:
** navy
*/

#include "main.h"

int get_pos_from_letter(char letter)
{
	int indice = 2;
	char compare = 'A';

	while (letter != compare && compare < 'I') {
		compare += 1;
		indice += 2;
	}
	return ((compare >= 'I') ? 84 : indice);
}

int check_if_player_was_hit(char **map, int letter, int line)
{
	int col = get_pos_from_letter(letter + 64);

	if (map[line + 1][col] != '.' && map[line + 1][col] != 'x' \
	&& map[line + 1][col] != 'o') {
		my_printf("%c%d: hit\n\n", letter + 64, line);
		map[line + 1][col] = 'x';
		return (1);
	}
	if (map[line + 1][col] == 'x') {
		my_printf("%c%d: missed\n\n", letter + 64, line);
		return (0);
	}
	my_printf("%c%d: missed\n\n", letter + 64, line);
	map[line + 1][col] = 'o';
	return (0);
}

void check_if_enemy_was_hit(char **map, int letter, int lin, int hit)
{
	int col = get_pos_from_letter(letter + 64);

	(hit == 1) ? my_printf("%c%d: hit\n\n", letter + 64, \
	lin) : my_printf("%c%d: missed\n\n", letter + 64, lin);
	map[lin + 1][col] = (hit != 1 && map[lin + 1][col] != 'x') ? 'o' : 'x';
}
