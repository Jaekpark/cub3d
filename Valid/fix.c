#include "fix.h"

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

int		parse_line(t_cub *cub, char *line)
{
	int ret;
	int index;

	ret = 0;
	if (!cub)
		return (-1);
	if (!(index = check_identifier(line)))
		return (-1);
	if (index >= 0 && index <= 6)
		ret = parsing_path(cub, line, index);
	else if (index == FLOOR_COL || index == CEIL_COL)
		ret = parsing_color(cub, line, index);
	else if (index == RESOLUTION)
		ret = parsing_resolution(cub, line);
	else if (index == MAP_LINE)
	{
		ret = parsing_map(&(cub->map), line);
		cub->is_map = 1;
	}
	else if (index == EMPTY_LINE && cub->is_map == 1)
	{

	}

}

int		read_file(int argc, char **argv, t_cub *cub)
{
	int		fd;
	int 	eof;
	int 	ret;
	char	*line;

	ret = 0;
	eof = 1;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (print_error(OPEN_ERR));
	if (argc >= 3 && strcmp(argv[2], SAVE) == 0)
		cub->save_opt = 1;
	while ((eof = get_next_line(fd, &line)) >= 0)
	{
		ret = parse_line(cub, line);
		free(line);
		if (ret < 0 || eof < 0)
			return (print_error(PARSING_ERR));
		if (eof == 0)
			break;
	}
	close(fd);
	return (1);
}
