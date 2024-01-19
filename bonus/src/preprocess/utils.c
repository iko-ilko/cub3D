#include "../include/cub3d.h"

void	exit_error(char *str, char *reason)
{
	printf("Error\n");
	if (reason != NULL)
		printf("%s: %s", str, reason);// ㄱㅐ해ㅇ이 필필요요한  상상황  있있는는지  체체크크
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

void	double_free(char ***p)
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