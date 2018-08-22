/*
** EPITECH PROJECT, 2018
** my_printf.c
** File description:
** printf
*/

#include <stdarg.h>
#include <unistd.h>

void my_print_nbr(int nb)
{
	int end_value;
	char neg = '-';

	if (nb < 0) {
		write(1, &neg, 1);
		nb = nb * -1;
	}
	end_value = nb % 10;
	nb = nb / 10;
	if (nb != 0)
		my_print_nbr(nb);
	end_value = end_value + '0';
	write(1, &end_value, 1);
}

void my_put_nbr(va_list list)
{
	int nb = va_arg(list, int);

	my_print_nbr(nb);
}

void my_putstr(va_list list)
{
	int i = 0;
	char *str = va_arg(list, char *);

	while (str[i] != '\0') {
		write(1, &str[i], 1);
		i++;
	}
}

void choose_option(char balise, va_list list)
{
	char c;

	switch (balise) {
		case 'c' :
		c = (char)va_arg(list, int);
		write(1, &c, 1);
		break;
		case 'd' :
		my_put_nbr(list);
		break;
		case 's' :
		my_putstr(list);
		break;
		default :
		break;
	}
}

void my_printf(char *str, ...)
{
	va_list list;
	int i = 0;

	va_start(list, str);
	while (str[i] != '\0') {
		if (str[i] == '%') {
			i++;
			choose_option(str[i], list);
		}
		else
			write(1, &str[i], 1);
		i++;
	}
}
