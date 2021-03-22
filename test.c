/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:27:34 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/22 20:39:08 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define OPEN_MAX 32
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

typedef struct	s_str
{
	char *content;
	struct s_str *next;
}				t_str;

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
	t_str 		*head_map;
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
	cub->head_map = malloc(sizeof(t_str) * 1);
	cub->col = 0;
	cub->row = 0;
}

int		ft_ismap(char *line)
{
	while (*line)
	{
		if (!strchr(VALID_CHAR, *line))
			return (-1);
		line++;
	}
	return (strlen(line));
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
	else if (strncmp(line, "ST", 2) == 0)
		return (CE_TEX);
	else if (ft_ismap(line))
		return (MAP_LINE);
	else
		return (-1);
}

char		*ft_strdup(char *s1)
{
	char	*s1_tmp;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen(s1);
	if (!(s1_tmp = malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (!s1)
		return (NULL);
	while (i < len)
	{
		s1_tmp[i] = s1[i];
		i++;
	}
	s1_tmp[i] = '\0';
	return (s1_tmp);
}

int			ft_strlen(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

t_str		*ft_lstnew(void *content)
{
	t_str	*lst;

	if (!(lst = malloc(sizeof(t_str) * 1)))
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

t_str	*ft_lstlast(t_str *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		ft_lstsize(t_str *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

void		ft_lstadd_back(t_str **lst, t_str *new)
{
	t_str	*last_add;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_add = ft_lstlast(*lst);
	last_add->next = new;
}

char		*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
		return (!s1 ? ft_strdup(s2) : ft_strdup(s1));
	if (!(result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char		*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&s[i]);
	return (NULL);
}

int			get_line(char **temp, char **line, char *newline)
{
	char			*tmp;

	tmp = NULL;
	*newline = '\0';
	*line = ft_strdup(*temp);
	if (*(newline + 1) == '\0')
	{
		free(*temp);
		*temp = NULL;
	}
	else
	{
		tmp = ft_strdup(newline + 1);
		free(*temp);
		*temp = tmp;
	}
	return (1);
}

int			check_temp(char **temp, char **line)
{
	char			*newline;

	newline = ft_strchr(*temp, '\n');
	if (*temp && newline != NULL)
		return (get_line(temp, line, newline));
	else if (newline == NULL && *temp)
	{
		*line = *temp;
		*temp = NULL;
	}
	else
		*line = ft_strdup("\0");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*temp[OPEN_MAX];
	char			buf[2];
	char			*newline;
	int				byte_count;

	newline = NULL;
	if (fd < 0)
		return (-1);
	while ((byte_count = read(fd, buf, 1)) > 0)
	{
		buf[byte_count] = '\0';
		temp[fd] = ft_strjoin(temp[fd], buf);
		//printf("byte cnt = %d\n", byte_count);
		if ((newline = ft_strchr(temp[fd], '\n')) != NULL)
			break ;
	}
	if (byte_count < 0)
		return (-1);
	return (check_temp(&temp[fd], line));
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

int parsing_resolution(t_cub *cub, char *line, int index)
{
	int i;
	int width;
	int height;
	char **display_size;

	i = 0;
	display_size = ft_split(line, ' ');
	while (display_size[i])
		i++;
	if (i != 3)
		return (-1);
	cub->width = atoi(display_size[1]);
	cub->height = atoi(display_size[2]);
	return (1);	
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

int parsing_map(t_cub *cub, char *line)
{
	t_str *temp;
	t_str *node;

	temp = NULL;
	node = NULL;
	printf("1111");
	printf("line = %s\n", line);
	if (!line)
		return (-1);
	if (cub->head_map->next == NULL)
	{
		node = ft_lstnew(line);
		cub->head_map->next = node;
	}
	else
	{
		node = ft_lstnew(line);
		ft_lstadd_back(&cub->head_map, node);
	}
	return (1);
}

int		parse_line(t_cub *cub, char *line)
{
	int ret;
	int index;

	ret = 0;
	printf("hi im here\n");
	if (!cub)
		return (-1);
	if (!(index = check_identifier(line)))
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

	ret = 1;
	line = NULL;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (print_error(OPEN_ERROR));
	if (argc >= 3 && strcmp(argv[2], SAVE_OPT) == 0)
		cub->save_opt = 1;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		parse_line(cub, line);
		free(line);
		if (ret == 0)
			break;
		if (ret < 0)
			return (print_error(PARSING_ERROR));
	}
	close(fd);
	return (1);
}

int main(int argc, char **argv)
{
	int ret;
	t_cub cub;
	t_str **map;

	init_cub(&cub);
	ret = read_file(argc, argv, &cub);
	printf("%d, %d\n", cub.width, cub.height);
	printf("%s\n", cub.path_no);
	printf("%s\n", cub.path_so);
	printf("%s\n", cub.path_ea);
	printf("%s\n", cub.path_we);
	printf("%s\n", cub.path_s);
	printf("floor tex%s\n", cub.path_ft);
	printf("ceilling tex%s\n", cub.path_ct);
	map = &(cub.head_map->next);
	printf("map %s\n", *(map)->content);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");

	return (0);
}
/* int main(void)
{
	int ret;
	int rgb;
	int eof;
	int par;
	t_str *temp;
	char test[3][7] = {
		{'a','b','c','d','e','f','\0'},
		{'1','2','3','4','5','6','\0'},
		{'4','4','5','5','6','5','\0'}
	};
	t_cub *cub;
	
	cub = malloc(sizeof(t_cub) * 1);
	init_cub(cub);
	ret = parsing_path(cub, "NO      ./texture/file.xpm", NO_TEX);
	rgb = parsing_color(cub, "F 255,255,255", FL_COLOR);
	par = parsing_map(cub, test[0], 1);
	par = parsing_map(cub, test[1], 1);
	par = parsing_map(cub, test[2], 0);
	temp = cub->head_map->next;
	printf("no tex dir = %s\n", cub->path_no);
	printf("color fl = %d\n", cub->floor_color);
	printf("map 0 = %s\n", temp->content);
	temp = temp->next;
	printf("map 1 = %s\n", temp->content);
	temp = temp->next;
	printf("map 2 = %s\n", temp->content);
	temp = temp->next;
	printf("map 3 = %s\n", temp->content);
	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
}*/