#include "fix.h"

int		ft_ismap(char *line)
{
	while (*line)
	{
		if (!ft_strchr(VALID_CHAR, *line))
			return (-1);
	}
	return (1);
}

int		ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >=97 && c <= 122))
		return (1);
	return (-1);
}
