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
char *get_info(int fd, char **map);
int count_nb_arg(char *line);

Test(navy, test_load_map)
{
	char **map = NULL;
	int fd = open("tests/pos1", O_RDONLY);

	map = create_empty_map(map);
	cr_assert_str_eq(get_info(fd, map), "2:H6:H7");
	close(fd);
	free_map(map);
}

Test(navy, test_count_nb_arg1)
{
	cr_assert_eq(count_nb_arg("2:H6:H7"), 3);
}

Test(navy, test_count_nb_arg2)
{
	cr_assert_eq(count_nb_arg("2:H6:H7:a:z:e:::j:,:s"), 11);
}
