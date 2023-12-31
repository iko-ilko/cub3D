/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:17:02 by ilko              #+#    #+#             */
/*   Updated: 2024/01/01 00:33:03 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

void	*if_error_gnl(t_list *backup)
{
	free(backup->str);
	backup->str = NULL;
	backup->len = 0;
	return (NULL);
}

char	*ft_strndup_gnl(const char *s1, int len)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*(res + i) = *(s1 + i);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}
