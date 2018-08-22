/*
** EPITECH PROJECT, 2018
** load_file.c
** File description:
** navy
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

int count_nb_arg(char *line)
{
	int i = 0;
	int count = 1;

	while (line[i] != '\0') {
		if (line[i] == ':')
			count++;
		i++;
	}
	return (count);
}

void free_map(char **map)
{
	int i = 0;

	if (map == NULL)
		return;
	while (map[i] != NULL) {
		free(map[i]);
		i++;
	}
	free(map);
}

char *get_info(int fd, char **map)
{
	char *info = NULL;
	int count;

	info = get_next_line(fd);
	if (info == NULL) {
		free(info);
		free_map(map);
		return (NULL);
	}
	count = count_nb_arg(info);
	if (count != 3) {
		free(info);
		free_map(map);
		return (NULL);
	}
	return (info);
}

char **load_info_into_map(int fd, char **map)
{
	char *info = NULL;
	int i = 0;

	while (i < 4) {
		info = get_info(fd, map);
		if (info == NULL)
			return (NULL);
		map = add_boat_to_map(map, info);
		if (map == NULL) {
			free(info);
			free_map(map);
			return (NULL);
		}
		free(info);
		i++;
	}
	return (map);
}

char **load_map(char *str)
{
	int fd = open(str, O_RDONLY);
	char **map = NULL;

	if (fd == -1)
		return (NULL);
	map = create_empty_map(map);
	if (map == NULL)
		return (NULL);
	map = load_info_into_map(fd, map);
	if (map == NULL)
		return (NULL);
	return (map);
}
