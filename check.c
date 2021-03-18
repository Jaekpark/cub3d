/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:17:15 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/18 18:32:11 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int		check_file_name(const char *file_name)
{
	int pos;

	if (!file_name)
		return (-1);
	if (strlen(file_name) < 5)
		return (-1);
	pos = strlen(file_name) - 4;
	while (pos--)
		file_name++;
	return (strcmp(file_name, MAP_EXTENSION));
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	return (strcmp(option, SAVE_OPT));
}

int		check_identifier(char *line)
{
	if (!line)
		return (EMPTY_LINE);
	else if (strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (strncmp(line, "NO", 2) == 0)
		return (NO_TEX);
	else if (strncmp(line, "SO", 2) == 0)
		return (SO_TEX);
	else if (strncmp(line, "EA", 2) == 0)
		return (EA_TEX);
	else if (strncmp(line, "WE", 2) == 0)
		return (WE_TEX);
	else if (strncmp(line, "S ", 2) == 0)
		return (SP_TEX);
	else if (strncmp(line, "F ", 2) == 0)
		return (FL_COLOR);
	else if (strncmp(line, "C ", 2) == 0)
		return (CE_COLOR);
	else if (strncmp(line, "FT", 2) == 0)
		return (FL_TEX);
	else if (strncmp(line, "CT", 2) == 0)
		return (CE_TEX);
	else if (ft_ismap(line))
		return (MAP_LINE);
	else
		return (-1);
}

int		check_argv(int argc, char **argv)
{
	if (argc < 2)
		return (print_error(NO_ARGUMENT));
	else if (argc >= 2)
	{
		if (argc > 3)
			return (print_error(TOO_MANY_ARGUMENT));
		else if (check_file_name(argv[1]) != 0)
			return (print_error(WRONG_FILENAME));
		else if (argc == 3)
			if (check_option(argv[2]) != 0)
				return (print_error(WRONG_OPTION));
	}
	return (1);
}
