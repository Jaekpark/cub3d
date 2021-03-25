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
