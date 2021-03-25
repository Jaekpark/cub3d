#include "fix.h"

t_list	*init_list(t_list *list)
{
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->curr = NULL;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

char	**init_path(char **path_tex, int size)
{
	int idx;

	idx = -1;
	if (!(path_tex = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (++idx <= size)
		path_tex[idx] = NULL;
	return (path_tex);
}

t_list	*init_cub(t_cub *cub)
{
	int size;

	size = 7
	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	cub->save_opt = 0;
	cub->width = 0;
	cub->height = 0;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->col = 0;
	cub->row = 0;
	cub->path_tex = init_path(cub->path_tex, size);
	return (cub);
}

void	clear_path_tex(char **path_tex)
{
	int size;
	int idx;

	idx = -1;
	size = 7;
	if (!path_tex)
		return ;
	while (++idx <= size)
		free(path_tex[idx]);
	free(path_tex);
}

void	clear_map(t_list *map)
{
	t_node	*temp;

	temp = NULL;
	while (map->head != NULL)
	{
		if (map->head->next == NULL)
		{
			free(map->head->line);
			free(map->head);
			break;
		}
		temp = map->head;
		while (temp->next->next != NULL)
			temp = temp->next;
		free(temp->next->line);
		free(temp->next);
		temp->next = NULL;
		if (temp != NULL)
			map->tail = temp;
	}
}
void	clear_cub(t_cub *cub)
{
	clear_path_tex(cub->path_tex);
	clear_map(cub->map);
	free(cub);
}

int		read_file(int argc, char **argv, t_cub *cub)
{
	int	fd;
	int ret;
	char	*line;

	ret = 0;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (print_error(OPEN_ERR));
	if (argc >= 3 && strcmp(argv[2], SAVE) == 0)
		cub->save_opt = 1;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{

	}
}
