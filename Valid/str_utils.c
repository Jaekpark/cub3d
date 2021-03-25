#include "fix.h"

char		*ft_strdup(char *s1)
{
	char	*s1_tmp;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
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
