/*
** EPITECH PROJECT, 2018
** Project navy
** File description:
** Main file.
*/

#include "main.h"

char *check_error_attack(int *error, char *attack)
{
	*error = 0;
	printw("attack: ");
	refresh();
	getstr(attack);
	if (my_strlen(attack) != 2 || attack[0] < 'A' || \
	attack[0] > 'H' || attack[1] < '0' || attack[1] > '8') {
		printw("wrong position\n");
		free(attack);
		*error = 1;
	}
	return (attack);
}

int letter_error(char *buff)
{
	if ((buff[2] < 65 && buff[2] > 72) ||
	(buff[10] < 65 && buff[10] > 72) ||
	(buff[18] < 65 && buff[18] > 72) || (buff[26] < 65 && buff[26] > 72))
		return (84);
	if ((buff[5] < 65 && buff[5] > 72) ||
	(buff[13] < 65 && buff[13] > 72) ||
	(buff[21] < 65 && buff[21] > 72) || (buff[29] < 65 && buff[29] > 72))
		return (84);
	if ((buff[3] < 49 && buff[3] > 56) ||
	(buff[11] < 49 && buff[11] > 56) ||
	(buff[19] < 49 && buff[19] > 56) || (buff[27] < 49 && buff[27] > 56))
		return (84);
	if ((buff[6] < 49 && buff[6] > 56) ||
	(buff[14] < 49 && buff[14] > 56) ||
	(buff[22] < 49 && buff[22] > 56) || (buff[30] < 49 && buff[30] > 56))
		return (84);
	return (0);
}

int error2(char *buff)
{
	if (buff[0] != '2' || buff[8] != '3' || buff[16] != '4' ||
	buff[24] != '5')
		return (84);
	if (buff[7] != '\n' || buff[15] != '\n' || buff[23] != '\n' ||
	buff[31] != '\n' || (buff[32] != '\0' && buff[32] != '\n'))
		return (84);
	if (buff[1] != ':' || buff[4] != ':' || buff[9] != ':'  ||
	buff[12] != ':' || buff[17] != ':' || buff[20] != ':' ||
	buff[25] != ':' || buff[28] != ':')
		return (84);
	if ((buff[2] + buff[3]) - (buff[5] + buff[6]) != -1)
		return (84);
	if ((buff[10] + buff[11]) - (buff[13] + buff[14]) != -2)
		return (84);
	if ((buff[18] + buff[19]) - (buff[21] + buff[22]) != -3)
		return (84);
	if ((buff[26] + buff[27]) - (buff[29] + buff[30]) != -4)
		return (84);
	return (0);
}

int map_error(char *str, char *buff)
{
	int i = 0;
	char **map = NULL;

	map = load_map(str);
	if (map == NULL) {
		free(map);
		return (84);
	}
	free(map);
	while (buff[i] != '\0')
		i++;
	if (i != 32 && i != 33)
		return (84);
	return (0);
}

int error(char *str)
{
	int fd = 0;
	char *buff = malloc(sizeof(char) * 100);

	if ((fd = open(str, O_RDONLY)) == -1)
		return (84);
	read(fd, buff, 100);
	if (map_error(str, buff) == 84 || error2(buff) == 84 ||
	letter_error(buff) == 84)
		return (84);
	close(fd);
	return (0);
}
