#include "fix.h"

void print_node(t_list *list)
{
	t_node *temp;

	temp = list->head;
	while (temp != NULL)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
}

void	print_cub(t_cub *cub)
{
	printf("width = %d\n", cub->width);
	printf("height = %d\n", cub->height);
	printf("map size = %d", ft_lstsize(cub->map));
	printf("floor color = %d\n", cub->floor_color);
	printf("ceiling color = %d\n", cub->ceiling_color);
	printf("north : %s\n", cub->path->north);
	printf("south : %s\n", cub->path->south);
	printf("east : %s\n", cub->path->east);
	printf("west : %s\n", cub->path->west);
	printf("sprite : %s\n", cub->path->sprite);
	printf("floor tex : %s\n", cub->path->floor);
	printf("ceiling tex : %s\n", cub->path->ceil);
	printf("map\n");
	print_node(cub->map);

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
	if (index >= NORTH_TEX && index <= CEIL_TEX)
		ret = parsing_path(cub, line, index);
	else if (index == FLOOR_COL || index == CEIL_COL)
		ret = parsing_color(cub, line, index);
	else if (index == RESOLUTION)
		ret = parsing_resolution(cub, line);
	else if (index == MAP_LINE)
		ret = parsing_map(cub, line);
	else if (index == EMPTY_LINE && cub->is_map == 1)
		ret = -1;
	else if (index == EMPTY_LINE && cub->is_map == 0)
		ret = 1;
	return (ret);
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
	while ((eof = get_next_line(fd, &line)) >= 0)
	{
		ret = parse_line(cub, line);
		free(line);
		if (ret < 0 || eof <= 0)
			break;
	}
	close(fd);
	return (1);
}

int main(int argc, char **argv)
{
	t_cub *cub;

	cub = init_cub(cub);
	print_cub(cub);
	clear_cub(cub);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}
