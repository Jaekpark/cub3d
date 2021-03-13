/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:59:30 by jaekpark          #+#    #+#             */
/*   Updated: 2020/11/11 20:47:59 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int			get_line(char **temp, char **line, char *newline)
{
	char			*tmp;

	*newline = '\0';
	*line = ft_strdup(*temp);
	if (!(*(newline + 1)))
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

	if (*temp && (newline = ft_strchr(*temp, '\n')) != NULL)
		return (get_line(temp, line, newline));
	else if (*temp)
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
	char			buf[BUFFER_SIZE + 1];
	char			*newline;
	int				byte_count;

	newline = NULL;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((byte_count = read(fd, buf, BUFFER_SIZE)) > 0)
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
