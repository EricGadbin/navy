/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

int turn1(global_t *global)
{
	struct sigaction hit = {.sa_sigaction = * hdl2, .sa_flags = SA_SIGINFO};
	char *attack = NULL;
	int error = 1;

	usleep(500);
	while (error != 0)
		attack = check_error_attack(&error, attack);
	send_signal(attack, global);
	sigaction(10, &hit, NULL);
	sigaction(12, &hit, NULL);
	pause();
	check_if_enemy_was_hit(global->map, attack[0] - 64, attack[1] - 48, gl);
	return (0);
}

int turn2(global_t *global)
{
	my_printf("waiting for enemy's attack...\n");
	global->sig1 = 0;
	global->sig2 = 0;
	receive_sig(global);
	if (gl == 1)
		kill(global->pid, 10);
	if (gl == 0)
		kill(global->pid, 12);
	return (0);
}
