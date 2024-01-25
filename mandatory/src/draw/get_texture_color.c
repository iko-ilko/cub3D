/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_color.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 04:17:34 by ilko              #+#    #+#             */
/*   Updated: 2024/01/26 04:49:15 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	get_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			return ((int)WEST);
		else
			return ((int)EAST);
	}
	else
	{
		if (ray->dir_y > 0)
			return ((int)NORTH);
		else
			return ((int)SOUTH);
	}
}

void	find_texture_x(t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * IMG_HOR);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		ray->tex_x = IMG_HOR - ray->tex_x - 1;
}

void	find_texture_y(t_ray *ray, int y)
{
	ray->tex_y = (y - ray->draw_start) * IMG_VER / \
	(ray->draw_end - ray->draw_start);
}

void	put_texture_color(t_data *data, t_ray *ray, int x, int y)
{
	find_texture_y(ray, y);
	ray->color = get_color(&data->image[ray->position], ray->tex_x, ray->tex_y);
	my_mlx_pixel_put(&data->palet, x, y, ray->color);
}
