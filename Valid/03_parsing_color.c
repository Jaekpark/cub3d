#include "fix.h"

int	check_color_space(char *line)
{
	int i;
	int num;
	int space;

	i = -1;
	num = 0;
	space = 0;
	while (line[++i] != '\0')
	{
		if (num == 0 && (ft_isnum(line[i]) == 1))
			num = 1;
		else if (num == 1 && line[i] == ' ')
			space = 1;
		else if (num == 1 && space == 1 && (ft_isnum(line[i]) == 1))
			return (-1);
		else if (line[i] == ',')
		{
			num = 0;
			space = 0;
		}
	}
	return (1);
}

int	check_color_char(char *line)
{
	int i;
	int comma;
	
	i = -1;
	comma = 0;
	if (!line)
		return (-1);
	if (line[0] != ' ')
		return (-1);
	while (line[++i] != '\0')
	{
		if (line[i] == ',')
			comma++;
		if (comma > 2)
			return (-1);
		else if (line[i] != ' ' && line[i] != ',' && (ft_isnum(line[i]) != 1))
			return (-1);
	}
	return (1);
}

int make_color(char **color)
{
	int r;
	int g;
	int b;
	int rgb;

	if (!color)
		return (-1);
	if (color[3] != NULL)
		return (-1);
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
		return (-1);
	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}
