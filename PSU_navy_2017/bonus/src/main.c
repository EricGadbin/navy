/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

int gl;

int init_ncurses(int argc)
{
	gl = 1;
	if (argc < 2 || argc  > 3)
		return (84);
	initscr();
	keypad(stdscr, true);
	curs_set(0);
	noecho();
	start_color();
	init_color(COLOR_BLACK, 0, 0, 0);
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_CYAN, 200, 200, 500);
	init_color(COLOR_YELLOW, 600, 700, 1000);
	init_pair(1, COLOR_RED, COLOR_YELLOW);
	init_pair(2, COLOR_CYAN, COLOR_YELLOW);
	init_pair(3, COLOR_CYAN, COLOR_YELLOW);
	init_pair(4, COLOR_GREEN, COLOR_YELLOW);
	wbkgd(stdscr, COLOR_PAIR(3));
	return (0);
}

int main(int argc, char *argv[])
{
	int i = 0;
	global_t *global = malloc(sizeof(*global));

	if (init_ncurses(argc) == 84)
		return (84);
	if (argc == 3) {
		if (error(argv[2]) == 84)
			return (84);
		printw("my_pid: %d\n", getpid());
		i = player_two(argv, global);
		return (i);
	}
	if (argc == 2) {
		if (error(argv[1]) == 84)
			return (84);
		printw("my_pid: %d\n", getpid());
		i = player_one(argv, global);
		return (i);
	}
	return (0);
}
