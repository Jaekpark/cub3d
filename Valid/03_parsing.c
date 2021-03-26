/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:03:47 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/26 14:17:41 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fix.h"

int parsing_path(t_cub *cub, char *line, int index)
{
	char **path;

	path = ft_split(line, ' ');
	if (!path)
		return (-1);
	else if (index == NORTH_TEX)
		cub->path->north = ft_strdup(path[1]);
	else if (index == SOUTH_TEX)
		cub->path->south = ft_strdup(path[1]);
	else if (index == EAST_TEX)
		cub->path->east = ft_strdup(path[1]);
	else if (index == WEST_TEX)
		cub->path->west = ft_strdup(path[1]);
	else if (index == SPRITE_TEX)
		cub->path->sprite = ft_strdup(path[1]);
	else if (index == FLOOR_TEX)
		cub->path->floor = ft_strdup(path[1]);
	else if (index == CEIL_TEX)
		cub->path->ceil = ft_strdup(path[1]);
	split_mem_free(path);
	return (1);
}

int make_color(char **color)
{
	int r;
	int g;
	int b;
	int rgb;

	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	rgb = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
	return (rgb);
}

int parsing_color(t_cub *cub, char *line, int index)
{
	int	rgb;
	int ret;
	char **info;
	char **color;

	info = ft_split(line, ' ');
	if (!(color = valid_color(info[1])))
	{
		split_mem_free(info);
		return (-1);
	}
	rgb = make_color(color);
	if (index == CEIL_COL)
		cub->ceiling_color = rgb;
	else if (index == FLOOR_COL)
		cub->floor_color = rgb;
	split_mem_free(info);
	split_mem_free(color);
	return (1);
}

int parsing_resolution(t_cub *cub, char *line)
{
	int i;
	int width;
	int height;
	char **display_size;

	i = 0;
	display_size = ft_split(line, ' ');
	if (display_size[3] != NULL)
	{
		split_mem_free((display_size));
		return (-1);
	}
	cub->width = ft_atoi(display_size[1]);
	cub->height = ft_atoi(display_size[2]);
	split_mem_free(display_size);
	return (1);	
}

int 	parsing_map(t_cub *cub, char *line)
{
	t_list	*tmp;
	t_node	*node;

	tmp = cub->map;
	cub->is_map = 1;
	if (!(node = malloc(sizeof(t_node))))
		return (-1);
	node->line = ft_strdup(line);
	node->next = NULL;
	tmp->curr = node;
	if (tmp->curr != NULL && (tmp->head == NULL && tmp->tail == NULL))
	{
		tmp->head = tmp->curr;
		tmp->tail = tmp->curr;
	}
	else
	{
		tmp->tail->next = tmp->curr;
		tmp->tail = tmp->curr;
	}
	return (1);
}
