/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:58:01 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/12 14:58:26 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	image_rotate(t_point **map, t_data *img, double h, double v)
{
	int	i;
	int	j;

	i = -1;
	while (++i < img->wy)
	{
		j = -1;
		while (++j < img->wx)
		{
			map[i][j].xx = (cos(-M_PI_4 + h) * map[i][j].x - sin(-M_PI_4 + h) * map[i][j].y) * img->relx;
			map[i][j].yy = (sin(-M_PI_4 + h) * map[i][j].x + cos(-M_PI_4 + h) * map[i][j].y) * img->rely;
			map[i][j].zz = map[i][j].z * img->relz * cos(v);
			map[i][j].yy = map[i][j].yy * sin(M_PI / 6 + v);
			map[i][j].yz = map[i][j].yy - map[i][j].zz;
		}
	}
}

