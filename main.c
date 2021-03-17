/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:57:39 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/03/17 21:50:33 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define MAP_EXTENSION ".cub"
#define SAVE_OPT "--save"
#define FILE_PATH "./maps/"
#define NO_ARGUMENT 0
#define WRONG_FILENAME 1
#define TOO_MANY_ARGUMENT 2
#define WRONG_OPTION 3
#define PARSING_ERROR 4
#define OPEN_ERROR 5

typedef struct	s_cub
{
	int			save_opt;
	int			width;
	int			height;
	int			floor_color;
	int			ceilling_color;
	char		*path_no;
	char		*path_so;
	char		*path_ea;
	char		*path_we;
	char		*path_s;
	char		**map;
	int			col;
	int			row;
}				t_cub;

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
	cub->save_opt = 0;
	cub->map = 0;
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
		printf("Error : Can't open file. Please check your map file.\n");
	return (-1);
}

int		check_file_name(const char *file_name)
{
	if (!file_name)
		return (-1);
	while (*file_name)
	{
		if (*file_name == '.' && ft_isapha(*(file_name + 1)))
			return (strcmp(file_name, MAP_EXTENSION));
		file_name++;
	}
	return (-1);
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	return (strcmp(option, SAVE_OPT));
}

int		read_cub(char *argv)
{
	int fd;
	char	*line;
	char	*file_name;
	t_cub cub;
	
	line = NULL;
	if (strncmp(argv, FILE_PATH, strlen(FILE_PATH)) != 0)
		if (!(file_name = ft_strjoin(FILE_PATH, argv)));
			return (print_error(PARSING_ERROR));
	else
		if (!(file_name = ft_strdup(argv)))
			return (print_error(PARSING_ERROR));
	if (!(fd = open(file_name, O_RDONLY)))
		return (print_error(OPEN_ERROR));
}

int		check_argv(int argc, char **argv)
{
	if (argc < 2)
		return (print_error(NO_ARGUMENT));
	else if (argc >= 2)
	{
		if (argc > 3)
			return (print_error(TOO_MANY_ARGUMENT));
		else if (check_file_name(argv[1]) != 0)
			return (print_error(WRONG_FILENAME));
		else if (argc == 3)
			if (check_option(argv[2]) != 0)
				return (print_error(WRONG_OPTION));
		if (read_cub(argv[1]) == -1)
			
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int ret;

	ret = 0;
	ret = check_argv(argc, argv);
	
	return (0);
}
