/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:03:47 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/18 19:46:26 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

int parsing_path(t_cub *cub, char *line, int index)
{
	char **path;

	path = ft_split(line, ' ');
	if (!path)
		return (-1);
	else if (index == NO_TEX)
		cub->path_no = strdup(path[1]);
	else if (index == SO_TEX)
		cub->path_so = strdup(path[1]);
	else if (index == EA_TEX)
		cub->path_ea = strdup(path[1]);
	else if (index == WE_TEX)
		cub->path_we = strdup(path[1]);
	else if (index == SP_TEX)
		cub->path_s = strdup(path[1]);
	else if (index == FL_TEX)
		cub->path_ft = strdup(path[1]);
	else if (index == CE_TEX)
		cub->path_ct = strdup(path[1]);
	split_mem_free(path);
	return (1);
}

int parsing_color(t_cub *cub, char *line, int index)
{
	int r;
	int g;
	int b;
	char **info;
	char **color;

	info = ft_split(line, ' ');
	if (!info)
		return (-1);
	color = ft_split(info[1], ',');
	split_mem_free(info);
	if (!color)
		return (-1);
	r = atoi(color[0]);
	g = atoi(color[1]);
	b = atoi(color[2]);
	split_mem_free(color);
	if (index == CE_COLOR)
		cub->ceilling_color = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
	else if (index == FL_COLOR)
		cub->floor_color = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
	return (1);
}

int parsing_resolution(t_cub *cub, char *line, int index)
{

}

int parsing_map(t_cub *cub, char *line, int index)
{

}
