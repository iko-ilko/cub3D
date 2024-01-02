#include "../include/cub3d.h"

void	exit_error(char *str, char *reason)
{
	printf("Error\n");
	if (reason != NULL)
		printf("%s: %s\n", str, reason);
	else
		printf("%s\n", str);
	exit(1);
}

void	single_free(char **p)//ㅍㅣㄹ요시 void *
{
	if (*p == NULL)
		return ;
	free(*p);
	*p = NULL;
}

void	free_double(char ***p)
{
	int	i;

	i = 0;
	if (*p == NULL)
		return ;
	while ((*p)[i])
	{
		free((*p)[i]);
		(*p)[i++] = NULL;
	}
	free(*p);
	*p = NULL;
}