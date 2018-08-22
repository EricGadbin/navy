/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

int gl;

int connection(global_t *global)
{
	struct sigaction ur1 = {.sa_sigaction = * hdl1, .sa_flags = SA_SIGINFO};

	my_printf("waiting for enemy connection...\n");
	sigaction(SIGUSR1, &ur1, NULL);
	pause();
	global->pid = gl;
	gl = 0;
	my_printf("\nenemy connected\n\n");
	return (0);
}

int structreset(global_t *global)
{
	global->sig1 = 0;
	global->sig2 = 0;
	return (0);
}

void display(global_t *global)
{
	my_printf("my positions:\n");
	for (int i = 0; global->boat_map[i] != NULL; i++)
	my_printf("%s\n", global->boat_map[i]);
	my_printf("\nenemy's positions:\n");
	for (int i = 0; global->map[i] != NULL; i++)
	my_printf("%s\n", global->map[i]);
	my_printf("\n");
}

int player_two(char **argv, global_t *global)
{
	int i = 0;

	global->boat_map = NULL;
	global->map = NULL;
	if (kill(my_getnbr(argv[1]), 10) == 0)
		my_printf("successfully connected\n\n");
	global->boat_map = load_map(argv[2]);
	global->map = create_empty_map(global->map);
	global->pid = my_getnbr(argv[1]);
	while (1) {
		i = check_end_game(global);
		if (i != 2)
			return (i);
		display(global);
		turn2(global);
		turn1(global);
		structreset(global);
	}
	return (0);
}

int player_one(char **argv, global_t *global)
{
	int i = 0;

	global->boat_map = NULL;
	global->map = NULL;
	connection(global);
	global->boat_map = load_map(argv[1]);
	global->map = create_empty_map(global->map);
	while (1) {
		i = check_end_game(global);
		if (i != 2)
			return (i);
		display(global);
		turn1(global);
		turn2(global);
		structreset(global);
	}
	return (0);
}
