/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:20 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/26 04:06:06 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* 플레인 단위벡터를 계산하는 함수. 수직이라는 점을 참고해서 만든다. */
t_vector	get_plane_vector(char c)
{
	if (c == 'N')
		return ((t_vector){-0.1 * tan(deg_to_rad(FOV / 2)), 0});
	else if (c == 'S')
		return ((t_vector){0.1 * tan(deg_to_rad(FOV / 2)), 0});
	else if (c == 'E')
		return ((t_vector){0, -0.1 * tan(deg_to_rad(FOV / 2))});
	else
		return ((t_vector){0, 0.1 * tan(deg_to_rad(FOV / 2))});
}

/* 플레이어의 시야의 단위벡터를 잡아주는 함수. 북쪽일 떄 -1 이라는 점이 중요하다. */
t_vector	get_player_sight(char c)
{
	if (c == 'N')
		return ((t_vector){0, -0.1});
	else if (c == 'S')
		return ((t_vector){0, 0.1});
	else if (c == 'E')
		return ((t_vector){0.1, 0});
	else
		return ((t_vector){-0.1, 0});
}

/* 맵에 있는 플레이어 표시를 바탕으로 플레이어의 맵좌표, 바라보는 방향벡터, 방향과 수직으로 존재하는 plane 벡터값을 만들어준다. */
t_point	get_point_data(t_data *data)
{
	t_point		res;
	int			i;
	int			j;

	i = 0;
	while (i < data->y_max)
	{
		j = 0;
		while (j < ft_strlen(data->map[i]) - 1)
		{
			if (ft_strchr("NESW", data->map[i][j]))
				break ;
			j++;
		}
		if (ft_strchr("NESW", data->map[i][j]))
			break ;
		i++;
	}
	res.pos.x = j + 0.5;
	res.pos.y = i + 0.5;
	res.dir = get_player_sight(data->map[i][j]);
	res.plane = get_plane_vector(data->map[i][j]);
	data->map[i][j] = '0';
	return (res);
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_HOR - 1;
	ray->dir_x = data->point.dir.x + data->point.plane.x * ray->camera_x;
	ray->dir_y = data->point.dir.y + data->point.plane.y * ray->camera_x;
	ray->map_x = (int)data->point.pos.x;
	ray->map_y = (int)data->point.pos.y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

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
		ray->sidedist_x = (ray->map_x + 1.0 - data->point.pos.x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (data->point.pos.y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - data->point.pos.y) * ray->deltadist_y;
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
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > data->x_max - 0.25
			|| ray->map_x > data->y_max - 1.25)
			break ;
		else if (data->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

void	calculate_line_height(t_ray *ray, t_data *data, t_point *point)
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

int	get_texture_index(t_data *data, t_ray *ray)
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

void	find_texture_x(t_data *data, t_ray *ray)
{
	ray->tex_x = (int)(ray->wall_x * IMG_HOR);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		ray->tex_x = IMG_HOR - ray->tex_x - 1;
}

void	find_texture_y(t_data *data, t_ray *ray, int y)
{
	ray->tex_y = (y - ray->draw_start) * IMG_VER / (ray->draw_end - ray->draw_start);
}

void	put_texture_color(t_data *data, t_ray *ray, int x, int y)
{
	find_texture_y(data, ray, y);
	ray->color = get_color(&data->image[ray->position], ray->tex_x, ray->tex_y);
	my_mlx_pixel_put(&data->palette, x, y, ray->color);
}

void	plot_line(t_data *data, int x, t_ray *ray)
{
	int	y;

	y = -1;
	while (++y < ray->draw_start)
		my_mlx_pixel_put(&data->palette, x, y, 0x0000ff);
	while (y >= ray->draw_start && y < ray->draw_end)
	{
		put_texture_color(data, ray, x, y);
		y++;
	}
	while (y < WIN_VER)
		my_mlx_pixel_put(&data->palette, x, y++, 0x00ff00);
}


void	put_minimap(t_data *data, int minimap_x, int minimap_y);

int	ray_casting(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_HOR)
	{
		init_ray(data, &ray, x);
		set_dda(data, &ray);
		perform_dda(data, &ray);
		calculate_line_height(&ray, data, &data->point);
		ray.position = get_texture_index(data, &ray);
		find_texture_x(data, &ray);
		plot_line(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->palette.img, 0, 0);
	put_minimap(data, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data		data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_HOR, WIN_VER, "cub3d");
	data.minimap.img = mlx_new_image(data.mlx, BLOCK_MAX * MULTIPLE, BLOCK_MAX * MULTIPLE);// can set macro//////
	preprocess(&data, argc, argv);
	data.palette.img = mlx_new_image(data.mlx, WIN_HOR, WIN_VER);
	data.palette.addr = mlx_get_data_addr(data.palette.img, &data.palette.bits_per_pixel, \
						&data.palette.line_length, &data.palette.endian);
	data.point = get_point_data(&data);
	ray_casting(&data);
	mlx_loop_hook(data.mlx, ray_casting, &data);
	mlx_hook(data.mlx_win, KEY_PRESS, 0, ft_key_action, &data);
	mlx_loop(data.mlx);
}
