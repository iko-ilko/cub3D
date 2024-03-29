/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:29:03 by ilko              #+#    #+#             */
/*   Updated: 2024/01/31 19:32:22 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	exit_error(char *str, char *reason)
{
	printf("Error\n");
	if (reason != NULL)
		printf("%s: %s", str, reason);
	else
		printf("%s\n", str);
	exit(1);
}

void	single_free(char **p)
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
