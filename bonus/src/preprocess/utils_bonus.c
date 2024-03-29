/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:17:42 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 16:28:35 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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
