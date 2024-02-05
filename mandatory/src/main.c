/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:20 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 19:27:21 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

t_point	get_point_data(t_data *data)
{
	t_point		res;
	int			i;
	int			j;

	i = 0;
	while (i < data->y_max)
	{
		j = 0;
		while (j < (int)ft_strlen(data->map[i]) - 1)
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
		calculate_line_height(&ray, &data->point);
		ray.position = get_texture_index(&ray);
		find_texture_x(&ray);
		plot_line(data, x, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->palet.img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIN_HOR, WIN_VER, "cub3d");
	preprocess(&data, argc, argv);
	data.palet.img = mlx_new_image(data.mlx, WIN_HOR, WIN_VER);
	data.palet.addr = mlx_get_data_addr(data.palet.img, \
	&data.palet.bits_per_pixel, &data.palet.line_length, &data.palet.endian);
	data.point = get_point_data(&data);
	ray_casting(&data);
	mlx_hook(data.mlx_win, KEY_PRESS, 0, ft_key_action, &data);
	mlx_hook(data.mlx_win, EXIT_BUTTON_PRESS, 0, goodbye, &data);
	mlx_loop(data.mlx);
}
