/*
** EPITECH PROJECT, 2018
** boat.c
** File description:
** navy
*/

#include "main.h"

int check_if_line_empty(int line_start, int line_end, int col_start, char **map)
{
	for (;line_end - line_start >= 0; line_start += 1) {
		if (map[line_start + 1][col_start] != '.')
			return (1);
	}
	return (0);
}

int check_if_col_empty(int col_start, int col_end, int line_start, char **map)
{
	for (; col_end - col_start >= 0; col_start += 2) {
		if (map[line_start + 1][col_start] != '.')
			return (1);
	}
	return (0);
}

int edit_map2(char **map, char *info, char indice)
{
	int l_start = info[3] - '0';
	int l_end = info[6] - '0';
	int c_start = get_pos_from_letter(info[2]);
	int c_end = get_pos_from_letter(info[5]);

	if (l_end - l_start == 0) {
		if (check_if_col_empty(c_start, c_end, l_start, map) == 1)
			return (1);
		for (;c_end - c_start >= 0; c_start += 2)
			map[l_start + 1][c_start] = indice;
	} else {
		if (check_if_line_empty(l_start, l_end, c_start, map) == 1)
			return (1);
		for (;l_end - l_start >= 0; l_start += 1)
			map[l_start + 1][c_start] = indice;
	}
	return (0);
}

int edit_map(char **map, char *info, char indice)
{
	int l_start = info[3] - '0';
	int l_end = info[6] - '0';
	int c_start = get_pos_from_letter(info[2]);
	int c_end = get_pos_from_letter(info[5]);

	if (c_start == 84 || l_start > 8 || l_start < 1 || \
	c_end == 84 || l_end > 8 || l_end < 1 || (c_end != c_start && \
	l_end != l_start) || (c_end - c_start != (indice - '0' - 1) * 2 && \
	l_end - l_start != indice - '0' - 1))
		return (1);
	if (edit_map2(map, info, indice))
		return (1);
	return (0);
}

char **add_boat_to_map(char **map, char *info)
{
	static char indice = '2';

	if (info[0] != indice && info[1] != ':' && info[4] != ':' && \
	my_strlen(info) != 7)
		return (NULL);
	if (edit_map(map, info, indice) == 1)
		return (NULL);
	indice += 1;
	if (indice == '6')
		indice = '2';
	return (map);
}
