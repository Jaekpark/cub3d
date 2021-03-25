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

t_list	*init_cub(t_cub *cub)
{
	int size;

	size = 7
	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	cub->is_map = 0;
	cub->save_opt = 0;
	cub->width = 0;
	cub->height = 0;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->col = 0;
	cub->row = 0;
	cub->path = init_tex(cub->path);
	return (cub);
}

t_tex	*init_tex(t_tex *tex)
{
	if (!(tex = malloc(sizeof(t_tex))))
		return (NULL);
	tex->north = NULL;
	tex->south = NULL;
	tex->east = NULL;
	tex->west = NULL;
	tex->sprite = NULL;
	tex->floor = NULL;
	tex->ceil = NULL;
	return (tex);
}