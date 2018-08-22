/*
** EPITECH PROJECT, 2018
** get_next_line.c
** File description:
** cpe
*/

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int	my_strlen(char const *str)
{
	int	i = 0;

	for (i = 0; str && str[i]; i++);
	return (i);
}

char *fill_str(char *str, char *tmp)
{
	static int i = 0;
	int count = 0;
	int j = 0;

	if (str == NULL || i >= my_strlen(str))
		return (NULL);
	while (str[i + count] != '\n' && str[i + count] != '\0')
		count++;
	if ((tmp = malloc(sizeof(char) * (count + 1))) == NULL)
		return (NULL);
	while (j != count){
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	i++;
	return (tmp);
}

char *copy_str(char *src, char *dest, int *stop)
{
	int i = 0;
	int j = 0;
	char *str = malloc(sizeof(char) * (my_strlen(dest) + \
	my_strlen(src) + 1));

	if (str == NULL)
		return (NULL);
	for (; dest && dest[i]; i += 1)
		str[i] = dest[i];
	while (src && src[j]) {
		if (src[j] == '\n')
			*stop = 1;
		str[i] = src[j];
		i += 1;
		j += 1;
	}
	str[i] = '\0';
	free(dest);
	return (str);
}

char *read_loop(int error, char *buff, char *str, int fd)
{
	int stop = 0;

	while (stop == 0 && error != 0) {
		error = read(fd, buff, READ_SIZE);
		if (error == -1)
			return (NULL);
		buff[error] = '\0';
		str = copy_str(buff, str, &stop);
	}
	return (str);
}

char *get_next_line(int fd)
{
	int error = 1;
	char buff[READ_SIZE + 1];
	char *tmp = NULL;
	static char *str = NULL;

	str = read_loop(error, buff, str, fd);
	tmp = fill_str(str, tmp);
	if (tmp == NULL && str != NULL) {
		free(str);
		str = NULL;
	}
	return (tmp);
}
