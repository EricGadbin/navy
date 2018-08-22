/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

int gl;

void my_help(void)
{
	my_printf("USAGE\n \
	./navy [first_player_pid] navy_positions\nDESCRIPTION\n \
	first_player_pid: only for the 2nd player. pid of the first player.\n \
	navy_positions: file representing the positions of the ships.\n");
}

int start_game(int argc, char *argv[])
{
	int i = 0;
	global_t *global = malloc(sizeof(*global));

	if (argc == 3) {
		if (error(argv[2]) == 84)
			return (84);
		my_printf("my_pid: %d\n", getpid());
		i = player_two(argv, global);
		return (i);
	}
	if (argc == 2) {
		if (error(argv[1]) == 84)
			return (84);
		my_printf("my_pid: %d\n", getpid());
		i = player_one(argv, global);
		return (i);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	int end = 0;

	gl = 1;
	if (argc < 2 || argc  > 3)
		return (84);
	if (argv[1][0] == '-' && argv[1][1] == 'h' && argv[1][2] == '\0') {
		my_help();
		return (0);
	}
	end = start_game(argc, argv);
	return (end);
}
