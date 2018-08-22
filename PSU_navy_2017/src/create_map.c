/*
** EPITECH PROJECT, 2018
** create_map.c
** File description:
** navy
*/

#include <stdlib.h>
#include "main.h"

char *fill_first_line(char *line)
{
	char *str = " |A B C D E F G H";
	int i = 0;

	line = malloc(sizeof(char) * 18);
	while (i < 17) {
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *fill_second_line(char *line)
{
	int i = 0;

	line = malloc(sizeof(char) * 18);
	while (i < 17) {
		line[i] = (i == 1) ? '+' : '-';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *fill_normal_lines(char *line)
{
	int i = 2;
	static char line_count = '1';

	line = malloc(sizeof(char) * 18);
	line[0] = line_count;
	line[1] = '|';
	while (i < 17) {
		line [i] = (i % 2 == 0) ? '.' : ' ';
		i++;
	}
	line[i] = '\0';
	line_count += 1;
	if (line_count == '9')
		line_count = '1';
	return (line);
}

char **create_empty_map(char **map)
{
	int i = 2;

	map = malloc(sizeof(char *) * 11);
	if (map == NULL)
		return (NULL);
	map[0] = fill_first_line(map[0]);
	map[1] = fill_second_line(map[1]);
	while (i <= 9) {
		map[i] = fill_normal_lines(map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}
