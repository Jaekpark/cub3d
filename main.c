/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:57:39 by parkjaekw         #+#    #+#             */
/*   Updated: 2021/03/18 16:57:44 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAP_EXTENSION ".cub"
#define SAVE_OPT "--save"
#define FILE_PATH "./maps/"
#define VALID_CHAR " 012NSEW"
#define NO_ARGUMENT 0
#define WRONG_FILENAME 1
#define TOO_MANY_ARGUMENT 2
#define WRONG_OPTION 3
#define PARSING_ERROR 4
#define OPEN_ERROR 5

#define NO_TEX 100
#define SO_TEX 101
#define EA_TEX 102
#define WE_TEX 103
#define SP_TEX 104
#define FL_TEX 105
#define CE_TEX 106
#define FL_COLOR 107
#define CE_COLOR 108
#define RESOLUTION 109
#define EMPTY_LINE 110
#define MAP_LINE 111

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
	char		*path_ft;
	char		*path_ct;
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
	cub->path_ft = 0;
	cub->path_ct = 0;
	cub->save_opt = 0;
	cub->map = 0;
	cub->col = 0;
	cub->row = 0;
}

int		ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >=97 && c <= 122))
		return (1);
	return (-1);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int i;
	int j;
	char *str;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
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

int		check_file_name(const char *file_name)
{
	int pos;

	if (!file_name)
		return (-1);
	if (strlen(file_name) < 5)
		return (-1);
	pos = strlen(file_name) - 4;
	while (pos--)
		file_name++;
	return (strcmp(file_name, MAP_EXTENSION));
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	return (strcmp(option, SAVE_OPT));
}

int		ft_ismap(char *line)
{
	while (*line)
	{
		if (!strchr(VALID_CHAR, *line))
			return (-1);
	}
	return (strlen(line));
}

int		check_identifier(char *line)
{
	if (!line)
		return (EMPTY_LINE);
	else if (strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (strncmp(line, "NO", 2) == 0)
		return (NO_TEX);
	else if (strncmp(line, "SO", 2) == 0)
		return (SO_TEX);
	else if (strncmp(line, "EA", 2) == 0)
		return (EA_TEX);
	else if (strncmp(line, "WE", 2) == 0)
		return (WE_TEX);
	else if (strncmp(line, "S ", 2) == 0)
		return (SP_TEX);
	else if (strncmp(line, "F ", 2) == 0)
		return (FL_COLOR);
	else if (strncmp(line, "C ", 2) == 0)
		return (CE_COLOR);
	else if (strncmp(line, "FT", 2) == 0)
		return (FL_TEX);
	else if (strncmp(line, "CT", 2) == 0)
		return (CE_TEX);
	else if (ft_ismap(line))
		return (MAP_LINE);
	else
		return (-1);
}

int		parse_line(t_cub *cub, char *line)
{
	int index;

	if (!cub)
		return (-1);
	if (!(index = check_identifier(line)));
		return (-1);
	if (index >= 100 && index <= 106)
		parsing_path(cub, line, index);
	else if (index == FL_COLOR || index == CE_COLOR)
		parsing_color(cub, line, index);
	else if (index == RESOLUTION)
		parsing_resolution(cub, line ,index);
	else if (index == MAP_LINE)
		parsing_map(cub, line, index);
	else if (index == EMPTY_LINE && cub->map != NULL)
		return (-1);
	return (1);
}


int		read_cub(int argc, char **argv, t_cub *cub)
{
	int		fd;
	int		ret;
	char	*line;
	t_cub	cub;
	
	ret = 0;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY) < 0))
		return (print_error(OPEN_ERROR));
	if (argc == 3 && strcmp(argv[2], SAVE_OPT) == 0)
		cub.save_opt = 1;
	while (get_next_line(fd, &line))
	{
		ret = parse_line(&cub, line);
		free(line);
		if (ret < 0)
			return (print_error(PARSING_ERROR));
	}
	return (1);
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
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int ret;
	t_cub cub;
	
	cub = init_cub(&cub);
	check_argv(argc, argv);
	read_cub(argc, argv, &cub);
	return (0);
}
