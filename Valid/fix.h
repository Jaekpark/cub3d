#ifndef FIX_H
# define FIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

# define MAP_EXTENSION ".cub"
# define SAVE "--save"
# define FILE_PATH "./maps/"
# define VALID_CHAR " 012NSEW"

#ifndef OPEN_MAX
# define OPEN_MAX 32
#endif

# define NO_ARG 100
# define WRONG_NAME 101
# define WRONG_OPT 102
# define PARSING_ERR 103
# define OPEN_ERR 104

# define NORTH_TEX 0
# define SOUTH_TEX 1
# define EAST_TEX 2
# define WEST_TEX 3
# define SPRITE_TEX 4
# define FLOOR_TEX 5
# define CEIL_TEX 6
# define FLOOR_COL 7
# define CEIL_COL 8
# define RESOLUTION 9
# define EMPTY_LINE 10
# define MAP_LINE 11

typedef struct s_node
{
	char	*line;
	struct s_node *next;
}	t_node;

typedef struct s_list
{
	struct s_node *curr;
	struct s_node *head;
	struct s_node *tail;
}	t_list;

typedef struct s_cub
{
	int	save_opt;
	int	width;
	int	height;
	int	floor_color;
	int	ceiling_color;
	char **path_tex;
	t_list *map;
	int col;
	int row;
}	t_cub;

int	get_next_line(int fd, char **line);

#endif
