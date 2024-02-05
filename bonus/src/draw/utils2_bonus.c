/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:06:54 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 15:06:56 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	ft_abs(double i)
{
	return ((i * (i >= 0) + -i * (i < 0)));
}

/**
 * degree 스케일의 각도값을 radian 으로 변경하는 함수.
*/
double	deg_to_rad(double deg)
{
	return (deg * 2 * M_PI / 360);
}
