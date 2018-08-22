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

	printw("waiting for enemy connexion...\n");
	sigaction(SIGUSR1, &ur1, NULL);
	refresh();
	pause();
	global->pid = gl;
	gl = 0;
	printw("\nenemy connected\n");
	printw("\nmy positions:\n");
	refresh();
	return (0);
}

void print_color(char **map, int *i, int *j)
{
	if (map[*i][*j] == 'x')
	attron(COLOR_PAIR(1));
	else if (map[*i][*j] == 'o')
	attron(COLOR_PAIR(4));
	else
	attron(COLOR_PAIR(2));
	addch(map[*i][*j]);
	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
}

void display(global_t *global)
{
	for (int i = 0; global->boat_map[i] != NULL; i++) {
		for (int j = 0; global->boat_map[i][j] != '\0'; j++) {
			print_color(global->boat_map, &i, &j);
		}
		printw("\n");
	}
	printw("\nenemy's positions:\n");
	for (int i = 0; global->map[i] != NULL; i++) {
		for (int j = 0; global->map[i][j] != '\0'; j++) {
			print_color(global->map, &i, &j);
		}
		printw("\n");
	}
	refresh();
}

int player_two(char **argv, global_t *global)
{
	int i = 0;

	global->boat_map = NULL;
	global->map = NULL;
	if (kill(my_getnbr(argv[1]), 10) == 0)
		printw("successfully connected\n");
	printw("\nmy positions:\n");
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
