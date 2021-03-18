/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:15:13 by jaekpark          #+#    #+#             */
/*   Updated: 2021/03/18 18:31:41 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

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

int		ft_ismap(char *line)
{
	while (*line)
	{
		if (!strchr(VALID_CHAR, *line))
			return (-1);
	}
	return (strlen(line));
}