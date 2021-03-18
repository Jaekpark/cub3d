/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:27:34 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/18 19:47:45 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# define MAP_EXTENSION ".cub"
# define SAVE_OPT "--save"
# define FILE_PATH "./maps/"
# define VALID_CHAR " 012NSEW"

# define NO_ARGUMENT 0
# define WRONG_FILENAME 1
# define TOO_MANY_ARGUMENT 2
# define WRONG_OPTION 3
# define PARSING_ERROR 4
# define OPEN_ERROR 5

# define NO_TEX 100
# define SO_TEX 101
# define EA_TEX 102
# define WE_TEX 103
# define SP_TEX 104
# define FL_TEX 105
# define CE_TEX 106
# define FL_COLOR 107
# define CE_COLOR 108
# define RESOLUTION 109
# define EMPTY_LINE 110
# define MAP_LINE 111

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

int			word_count(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int			*word_size(char const *s, char c)
{
	int		*arr;
	int		size;
	int		i;
	int		j;

	if (!(arr = malloc(sizeof(int) * word_count(s, c))))
		return (NULL);
	size = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size++;
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				arr[j] = size;
				size = 0;
				j++;
			}
		}
		i++;
	}
	return (arr);
}

void		mem_allocate(char **dest, int *size, int count)
{
	int		i;

	i = 0;
	dest[count] = NULL;
	while (count)
	{
		dest[i] = malloc(sizeof(char) * size[i] + 1);
		i++;
		count--;
	}
}

void			split_mem_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		*size;
	char	**dest;

	if (!s || !(dest = (char **)malloc(sizeof(char *) * word_count(s, c) + 1)))
		return (NULL);
	size = word_size(s, c);
	mem_allocate(dest, size, word_count(s, c));
	i = -1;
	j = 0;
	k = 0;
	while (s[++i])
		if (s[i] != c)
		{
			dest[j][k++] = s[i];
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				dest[j++][k] = '\0';
				k = 0;
			}
		}
	free(size);
	return (dest);
}

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
	int r;
	int g;
	int b;
	char **info;
	char **color;

	info = ft_split(line, ' ');
	if (!info)
		return (-1);
	color = ft_split(info[1], ',');
	split_mem_free(info);
	if (!color)
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

int main(void)
{
	int ret;
	int rgb;
	t_cub *cub;
	
	cub = malloc(sizeof(t_cub) * 1);
	init_cub(cub);
	ret = parsing_path(cub, "NO      ./texture/file.xpm", NO_TEX);
	rgb = parsing_color(cub, "F 255,255,255", FL_COLOR);
	printf("no tex dir = %s\n", cub->path_ft);
	printf("color fl = %d\n", cub->floor_color);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
}