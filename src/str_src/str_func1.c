#include "../../include/cub3d.h"

int	ft_strlen(char *s)
{
	int	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		all_len;
	char	*res;

	all_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (all_len + 1));
	if (res == 0)
		exit_error("malloc failed", NULL);
	i = 0;
	if (s1 != NULL)
	{
		while (*s1)
			res[i++] = *(s1++);
	}
	while (*s2)
		res[i++] = *(s2++);
	res[i] = '\0';
	return (res);
}