/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:20 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/21 18:51:53 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* 플레인 단위벡터를 계산하는 함수. 수직이라는 점을 참고해서 만든다. */
t_vector	get_plane_vector(char c)
{
	if (c == 'N')
		return ((t_vector){-0.2 * tan(deg_to_rad(FOV / 2)), 0});
	else if (c == 'S')
		return ((t_vector){0.2 * tan(deg_to_rad(FOV / 2)), 0});
	else if (c == 'E')
		return ((t_vector){0, -0.2 * tan(deg_to_rad(FOV / 2))});
	else
		return ((t_vector){0, 0.2 * tan(deg_to_rad(FOV / 2))});
}

/* 플레이어의 시야의 단위벡터를 잡아주는 함수. 북쪽일 떄 -1 이라는 점이 중요하다. */
t_vector	get_player_sight(char c)
{
	if (c == 'N')
		return ((t_vector){0, -0.2});
	else if (c == 'S')
		return ((t_vector){0, 0.2});
	else if (c == 'E')
		return ((t_vector){0.2, 0});
	else
		return ((t_vector){-0.2, 0});
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
	res.player.x = j + 0.5;
	res.player.y = i + 0.5;
	res.sight = get_player_sight(data->map[i][j]);
	res.plane = get_plane_vector(data->map[i][j]);
	return (res);
}

void	ray_casting(t_data *data)
{
	t_vector	ray;
	int			x;
	double		camera_x;
	int			height;

	camera_x = 0;
	x = 0;
	while (x < WIN_HOR)
	{
		camera_x = ((2 * (double)x / WIN_HOR) - 1);
		ray = vector_calculate(data->point.sight,\
			vector_multiple(data->point.plane, camera_x), PLUS);
		height = get_wall_height(data, data->point, ray);
		plot_line(data, x, height);
		x++;
	}
}

unsigned int	img_pick_color(t_image *img, int x, int y)
{
	unsigned int	*point;
	unsigned int	*dst;

	point = (unsigned int *)(img->addr + img->line_length * y + img->bits_per_pixel / 8 * x);

	// dst = (unsigned int *)img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*point);
}

int main(int argc, char **argv)
{
	t_data		data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_HOR, WIN_VER, "cub3d");
	preprocess(&data, argc, argv);
	data.palette.img = mlx_new_image(data.mlx, WIN_HOR, WIN_VER);
	data.palette.addr = mlx_get_data_addr(data.palette.img, &data.palette.bits_per_pixel, \
						&data.palette.line_length, &data.palette.endian);
	data.point = get_point_data(&data);
	ray_casting(&data);
	mlx_hook(data.mlx_win, KEY_PRESS, 0, ft_key_action, &data);
	mlx_loop(data.mlx);
}
