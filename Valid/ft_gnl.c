#include "fix.h"

static int			get_line(char **temp, char **line, char *newline)
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

static int			check_temp(char **temp, char **line)
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
		if ((newline = ft_strchr(temp[fd], '\n')) != NULL)
			break ;
	}
	if (byte_count < 0)
		return (-1);
	return (check_temp(&temp[fd], line));
}
