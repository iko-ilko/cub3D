#include "../include/cub3d.h"

void	exit_error(char *str, char *reason)
{
	if (reason != NULL)
		printf("%s%s\n", str, reason);
	else
		printf("%s\n", str);
	exit(1);
}

void	one_free(char **p)
{
	int	i;

	i = 0;
	while (*p[i])
	{
		free(*p[i]);
		*p[i++] = NULL;
	}
	free(*p);
	*p = NULL;
}