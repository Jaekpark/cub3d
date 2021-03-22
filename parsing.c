/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:03:47 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/22 18:49:31 by jaekpark         ###   ########.fr       */
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
	int i;
	int r;
	int g;
	int b;
	char **info;
	char **color;

	i = 0;
	info = ft_split(line, ' ');
	if (!info)
		return (-1);
	color = ft_split(info[1], ',');
	split_mem_free(info);
	if (color[i])
		i++;
	if (i != 3)
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
	int i;
	int width;
	int height;
	char **display_size;

	i = 0;
	display_size = ft_split(line, ' ');
	while (display_size[i])
		i++;
	if (i != 3)
		return (-1);
	cub->width = atoi(display_size[1]);
	cub->height = atoi(display_size[2]);
	return (1);	
}

int parsing_map(t_cub *cub, char *line, int eof)
{
	t_str *temp;
	t_str *node;

	temp = NULL;
	node = malloc(sizeof(t_str) * 1);
	if (cub->head_map = NULL)
	{	
		cub->head_map = malloc(sizeof(t_str) * 1);
		cub->head_map->next = node;
		node->content = strdup(line);
		node->next = NULL;
	}
	else if (cub->head_map != NULL)
	{
		while (cub->head_map->next != NULL)
			temp = cub->head_map->next;
		temp->next = node;
		node->content = strdup(line);
		node->next = NULL;
	}
	if (eof == 0 && node->next != NULL)
		return (-1);
	return (1);
}
