/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

int gl;

void send_letter(char *attack, global_t *global)
{
	int letter = 0;

	letter = attack[0] - 64;
	while (letter != 0) {
		kill(global->pid, 10);
		usleep(500);
		letter--;
	}
	kill(global->pid, 12);
}

void send_num(char *attack, global_t *global)
{
	int num = 0;

	num = attack[1] - 48;
	while (num != 0) {
		kill(global->pid, 10);
		usleep(500);
		num--;
	}
	kill(global->pid, 12);
}

int send_signal(char *attack, global_t *global)
{
	send_letter(attack, global);
	pause();
	send_num(attack, global);
	return (0);
}

void receive_sig(global_t *global)
{
	struct sigaction u1 = {.sa_sigaction = * hdl2, .sa_flags = SA_SIGINFO};

	gl = 1;
	sigaction(10, &u1, NULL);
	sigaction(12, &u1, NULL);
	while (gl == 1) {
		pause();
		if (gl == 1)
		global->sig1 += 1;
	}
	gl = 1;
	kill(global->pid, 10);
	while (gl == 1) {
		pause();
		if (gl == 1)
		global->sig2 += 1;
	}
	gl = 0;
	gl = check_if_player_was_hit(global->boat_map, global->sig1, \
		global->sig2);
}
