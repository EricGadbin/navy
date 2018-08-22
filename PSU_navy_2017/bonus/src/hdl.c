/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

int gl;

void hdl1(int sig, siginfo_t *siginfo, void *context)
{
	gl = siginfo->si_pid;
	(void)sig;
	(void)context;
}

void hdl2(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == 10)
		gl = 1;
	if (sig == 12)
		gl = 0;
	(void)siginfo;
	(void)context;
}
