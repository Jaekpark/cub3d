/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:57:39 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/03/22 19:38:18 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

void		init_cub(t_cub *cub)
{
	cub->ceilling_color = 0;
	cub->floor_color = 0;
	cub->height = 0;
	cub->width = 0;
	cub->path_ea = 0;
	cub->path_no = 0;
	cub->path_s = 0;
	cub->path_so = 0;
	cub->path_we = 0;
	cub->path_ft = 0;
	cub->path_ct = 0;
	cub->save_opt = 0;
	cub->head_map = malloc(sizeof(t_str) * 1);
	cub->head_map->content = NULL;
	cub->head_map->next = NULL;
	cub->col = 0;
	cub->row = 0;
}

int		print_error(int error)
{
	if (error == NO_ARGUMENT)
		printf("Error : Argument does not exists.\n");
	else if (error == WRONG_FILENAME)
		printf("Error : Wrong file name. Please check your file name.\n");
	else if (error == TOO_MANY_ARGUMENT)
		printf("Error : Too many argument.\n");
	else if (error == WRONG_OPTION)
		printf("Error : Unacceptable option. Using '--save' option.\n");
	else if (error == PARSING_ERROR)
		printf("Error : Parsing error. Please check your map file.\n");
	else if (error == OPEN_ERROR)
		printf("Error : Can't open file. Please check your file name or directory.\n");
	return (-1);
}

int		parse_line(t_cub *cub, char *line)
{
	int ret;
	int index;

	if (!cub)
		return (-1);
	if (!(index = check_identifier(line)));
		return (-1);
	if (index >= 100 && index <= 106)
		ret = parsing_path(cub, line, index);
	else if (index == FL_COLOR || index == CE_COLOR)
		ret = parsing_color(cub, line, index);
	else if (index == RESOLUTION)
		ret = parsing_resolution(cub, line ,index);
	else if (index == MAP_LINE)
		ret = parsing_map(cub, line);
	else if (index == EMPTY_LINE && cub->head_map->next->content != NULL)
		return (-1);
	return (ret);
}

int		read_file(int argc, char **argv, t_cub *cub)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY) < 0))
		return (print_error(OPEN_ERROR));
	if (argc == 3 && strcmp(argv[2], SAVE_OPT) == 0)
		cub->save_opt = 1;
	while (ret = get_next_line(fd, &line) >= 0)
	{
		parse_line(cub, line);
		free(line);
		if (ret < 0)
			return (print_error(PARSING_ERROR));
		if (ret == 0)
			break;
	}
	return (1);
}

/*int		main(int argc, char **argv)
{
	int ret;
	t_cub cub;
	
	cub = init_cub(&cub);
	check_argv(argc, argv);
	read_cub(argc, argv, &cub);
	return (0);
}*/