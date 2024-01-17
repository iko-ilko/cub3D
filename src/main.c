/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:20 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/16 22:49:24 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* 플레인 단위벡터를 계산하는 함수. 수직이라는 점을 참고해서 만든다. */
t_vector	get_plane_vector(char c)
{ 
	if (c == 'N')
		return ((t_vector){-tan(deg_to_rad(FOV / 2)), 0, 0});
	else if (c == 'S')
		return ((t_vector){tan(deg_to_rad(FOV / 2)), 0, 0});
	else if (c == 'E')
		return ((t_vector){0, -tan(deg_to_rad(FOV / 2)), 0});
	else
		return ((t_vector){0, tan(deg_to_rad(FOV / 2)), 0});
}

/* 플레이어의 시야의 단위벡터를 잡아주는 함수. 북쪽일 떄 -1 이라는 점이 중요하다. */
t_vector	get_player_sight(char c)
{
	if (c == 'N')
		return ((t_vector){0, -1, 0});
	else if (c == 'S')
		return ((t_vector){0, 1, 0});
	else if (c == 'E')
		return ((t_vector){1, 0, 0});
	else
		return ((t_vector){-1, 0, 0});
}

/* 맵에 있는 플레이어 표시를 바탕으로 플레이어의 맵좌표, 바라보는 방향벡터, 방향과 수직으로 존재하는 plane 벡터값을 만들어준다. */
t_point	get_point_data(t_data *data)
{
	t_point		res;
	int			i;
	int			j;

	i = 0;
	while (i < data->x_max)
	{
		j = 0;
		while (j < data->y_max)
		{
			if (ft_strchr("NSEW", data->map[i][j]))
				break ;
			j++;
		}
		i++;
	}
	res.player.x = j + 0.5;
	res.player.y = i + 0.5;
	res.player.z = 0;
	res.sight = get_player_sight(data->map[i][j]);
	res.plane = get_plane_vector(data->map[i][j]);
	return (res);
}

double	get_wall_hight(t_data *data, t_point point, t_vector ray)
{
	t_vector	dist;
	t_vector	side;
	int			side_wall;
	double		wall_dist;

	get_dist(point, &dist, ray);
	get_side(point, &side, dist, ray);
	side_wall = ft_dda(data, point, dist, &side, ray);
	if (side_wall == 0)
		wall_dist = side.x - dist.x;
	else
		wall_dist = side.y - dist.y;
	return ((int)(WIN_VER / wall_dist));
}

void	ray_casting(t_data *data, t_point point)
{
	t_vector	ray;
	int			x;
	double		camera_x;
	int			height;

	camera_x = 0;
	x = 0;
	while (camera_x < WIN_HOR)
	{
		camera_x = 2 * camera_x / WIN_HOR - 1;
		ray = vector_calculate(point.sight,\
			vector_multiple(point.plane, camera_x), PLUS);
		height = get_wall_hight(data, point, ray);
		plot_line(data, x, height);
		x++;
	}
}

int main(int argc, char **argv)
{
	t_data		data;
	t_point		point;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_HOR, WIN_VER, "cub3d");
	preprocess(&data, argc, argv);
	data.img = mlx_new_image(data.mlx, WIN_HOR, WIN_VER);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, \
	&data.line_length, &data.endian);
	point = get_point_data(&data);
	ray_casting(&data, point);

	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook(data.mlx_win, 2, 0, ft_key_action, &data);
	mlx_loop(data.mlx);
}
