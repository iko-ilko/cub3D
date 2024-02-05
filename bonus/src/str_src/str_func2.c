/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:06:53 by ilko              #+#    #+#             */
/*   Updated: 2024/02/05 16:28:44 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	my_atoi_cub(char *str)
{
	int	result;
	int	sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	result = 0;
	while (*str != '\0' && *str != '\n')
	{
		if (*str < '0' || *str > '9')
			exit_error(RGB_VALUE_ERROR, str);
		result = result * 10 + *(str++) - '0';
		if (result / 1000 > 0)
			exit_error(RGB_VALUE_ERROR, str);
	}
	return (result * sign);
}

char	*my_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
