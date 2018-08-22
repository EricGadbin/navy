/*
** EPITECH PROJECT, 2017
** getnbr
** File description:
** getnbr
*/

int nbr_maker(char *str, int i)
{
	int nb = 0;

	while (str[i] >= '0' && str[i] <= '9') {
		nb = nb * 10;
		nb = nb + str[i] - '0';
		i++;
	}
	return (nb);
}

int my_getnbr(char *str)
{
	int nb = 0;
	int j = 0;
	int i = 0;

	while (str && str[i] != '\0' && nb == 0) {
		if ((str[i] <= 47 && str[i] != 45) || \
		(str[i] >= 58 && str[i] != 45)) {
			return (-991);
			}
		if (str[i] == '-')
			j++;
		if (str[i] >= '0' && str[i] <= '9')
			nb = nbr_maker(str, i);
		i++;
	}
	if (j % 2 == 1)
		nb = - nb;
	return (nb);
}
