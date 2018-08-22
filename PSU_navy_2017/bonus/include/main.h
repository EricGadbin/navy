/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Header file
*/

#ifndef MAIN_H_
	#define MAIN_H_
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>
	#include <signal.h>
	#include <string.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <ncurses.h>

	extern int gl;

	typedef struct global_s {
		int pid;
		int sig1;
		int sig2;
		char **map;
		char **boat_map;
	}global_t;

	char **load_map(char *);
	char **create_empty_map(char **);
	char *get_next_line(int);
	int my_getnbr(char *);
	void my_printf(char *str, ...);
	int connection(global_t *);
	int player_two(char **, global_t *);
	int player_one(char **, global_t *);
	void send_letter(char *, global_t *);
	void send_num(char *, global_t *);
	int send_signal(char *, global_t *);
	void receive_sig(global_t *);
	void hdl1(int sig, siginfo_t *, void *);
	void hdl2(int sig, siginfo_t *, void *);
	int my_strlen(char *);
	char **add_boat_to_map(char **map, char *info);
	int get_pos_from_letter(char);
	int check_if_player_was_hit(char **map, int letter, int line);
	void check_if_enemy_was_hit(char **map, int letter, int line, int hit);
	int check_end_game(global_t *);
	void display(global_t *);
	int error(char *);
	int turn1(global_t *);
	int turn2(global_t *);
	char *check_error_attack(int *, char *);
	int structreset(global_t *global);
#endif
