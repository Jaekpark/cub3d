/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:17:15 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/26 14:23:52 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fix.h"

char	**check_color(char *info)
{
	char	**color;
	int comma;
	int	i;

	i = -1;
	comma = 0;
	while (info[++i] != '\0')
	{
		if (!ft_isnum(info[i]) && info[i] != ',')
			return (NULL);
		if (info[i] == ',')
			comma++;
		if (comma > 2)
			return (NULL);
	}
	color = ft_split(info, ',');
	if (color[3] != NULL)
	{
		split_mem_free(color);
		return (NULL);
	}
	return (color);
}

int		check_file_name(const char *file_name)
{
	int pos;

	if (!file_name)
		return (-1);
	if (ft_strlen((char *)file_name) < 5)
		return (-1);
	pos = ft_strlen((char *)file_name) - 4;
	while (pos--)
		file_name++;
	return (ft_strcmp((char *)file_name, MAP_EXTENSION));
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	return (ft_strcmp((char *)option, SAVE));
}

int		check_identifier(char *line)
{
	if (line[0] == 0)
		return (EMPTY_LINE);
	else if (ft_strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (NORTH_TEX);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (SOUTH_TEX);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (EAST_TEX);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (WEST_TEX);
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (SPRITE_TEX);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR_COL);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEIL_COL);
	else if (ft_strncmp(line, "FT", 2) == 0)
		return (FLOOR_TEX);
	else if (ft_strncmp(line, "CT", 2) == 0)
		return (CEIL_TEX);
	else if (ft_ismap(line) == 1)
		return (MAP_LINE);
	else
		return (-1);
}

int		check_argv(int argc, char **argv, t_cub *cub)
{
	if (argc < 2)
		return (print_error(NO_ARG));
	else if (argc >= 2)
	{
		if (check_file_name(argv[1]) != 0)
			return (print_error(WRONG_NAME));
		else if (argc >= 3)
		{
			if (check_option(argv[2]) != 0)
				return (print_error(WRONG_OPT));
			else if (check_option(argv[2] == 0) == 0)
				cub->save_opt = 1;
		}
	}
	return (1);
}
