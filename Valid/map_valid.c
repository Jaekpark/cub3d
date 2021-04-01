#include "fix.h"

int	valid_map(char	**map_buffer)
{
	int x_size;
	int y_size;
	int	padding;
	int x;
	int y;
	
	x = 0;
	y = 0;
	x_size = 0;
	y_size = ft_strlen(map_buffer[0]);
	while (map_buffer[x_size] != NULL)
		x_size++;
	while (map_buffer)
}

int is_wall(char **visited, char **map_buffer, int x, int y)
{
	static int sx;
	static int sy;

	sx = x;
	sy = y;

	visited[x][y] = 'v';
	if (map_buffer[x][y + 1] == '1')
		return (is_wall(visited, map_buffer, x, y + 1));
	else if (map_buffer[x + 1][y] == '1')
		return (is_wall(visited, map_buffer, x + 1, y));
	else if (map_buffer[x][y - 1] == '1')
		return (is_wall(visited, map_buffer, x, y - 1));
	else if (map_buffer[x - 1][y] == '1')
		return (is_wall(visited, map_buffer, x - 1, y));
	else if (visited[x][y] == 'v')
		return (-1);
	return (1);
}	

int set_base(char **map_buffer)
{
	int x;
	int y;
	int base_x;
	int base_y;

	x = 0;
	y = 0;
	base_x = -1;
	base_y = -1;
	while (map_buffer[x][y] != '\0')
	{
		if (map_buffer[x][y] == '1')
		{
			base_x = x;
			base_y = y;
			break;
		}
		y++;
	}

}
