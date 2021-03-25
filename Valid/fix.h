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

# define OPEN_MAX 32
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
}				t_node;

typedef struct s_list
{
	struct s_node *curr;
	struct s_node *head;
	struct s_node *tail;
}	t_list;

typedef struct s_tex
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
	char	*floor;
	char	*ceil;
}	t_tex;

typedef struct s_cub
{
	int is_map;
	int width;
	int height;
	int col;
	int row;
	int	save_opt;
	int floor_color;
	int ceiling_color;
	t_list	*map;
	t_tex	*path;
}	t_cub;



// ft_is~
int		ft_ismap(char *line);
int		ft_isalpha(char c);

// gnl
int		get_next_line(int fd, char **line);

// split
int		ft_split(char const *s, char c);
void	split_mem_free(char **str);

// parsing
int		parsing_path(t_cub *cub, char *line ,int index);
int		parsing_color(t_cub *cub, char *line, int index);
int		parsing_resolution(t_cub *cub, char *line);
int		parsing_map(t_list **map, char *line);

#endif
