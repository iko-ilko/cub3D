/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:06:47 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 19:35:48 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	set_dda(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (data->point.pos.x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - data->point.pos.x) \
							* ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->point.pos.y - ray->map_y) \
							* ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->point.pos.y) \
							* ray->deltadist_y;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 1 - 2 * x / (double)WIN_HOR;
	ray->dir_x = data->point.dir.x + data->point.plane.x * ray->camera_x;
	ray->dir_y = data->point.dir.y + data->point.plane.y * ray->camera_x;
	ray->map_x = (int)data->point.pos.x;
	ray->map_y = (int)data->point.pos.y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

void	calculate_line_height(t_ray *ray, t_point *point)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)((double)WIN_VER / ray->wall_dist * 5);
	ray->draw_start = -(ray->line_height) / 2 + WIN_VER / 2;
	ray->draw_end = ray->line_height / 2 + WIN_VER / 2;
	if (ray->side == 0)
		ray->wall_x = point->pos.y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = point->pos.x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	plot_line(t_data *data, int x, t_ray *ray)
{
	int	y;

	y = -1;
	while (++y < ray->draw_start)
		my_mlx_pixel_put(&data->palet, x, y, data->ceiling_color);
	while (y >= ray->draw_start && y < ray->draw_end)
	{
		put_texture_color(data, ray, x, y);
		y++;
	}
	while (y < WIN_VER)
		my_mlx_pixel_put(&data->palet, x, y++, data->floor_color);
}
