/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:19:15 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 16:30:40 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

void	start_minimap(double start[2], t_vector player_pos)
{
	int		offset;

	offset = (BLOCK - 1) / 2;
	start[Y] = player_pos.y - offset;
	start[X] = player_pos.x - offset;
	if (player_pos.y - offset < 0)
		start[Y] = 0;
	if (player_pos.x - offset < 0)
		start[X] = 0;
}

void	draw_player(t_data *data, double start[2])
{
	int	p_pos[2];
	int	radius;
	int	i;
	int	j;

	p_pos[Y] = (int)((data->point.pos.y - start[Y]) * (double)MULTI);
	p_pos[X] = (int)((data->point.pos.x - start[X]) * (double)MULTI);
	radius = MULTI / 2 - 1;
	i = p_pos[Y] - radius;
	while (i <= p_pos[Y] + radius)
	{
		j = p_pos[X] - radius;
		while (j <= p_pos[X] + radius)
		{
			if ((i - p_pos[Y]) * (i - p_pos[Y]) + \
				(j - p_pos[X]) * (j - p_pos[X]) <= radius * radius)
				my_mlx_pixel_put(&data->minimap, j, i, 0x265AEB);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *d, char **map)
{
	double	start[2];
	int		idx[2];
	int		i;
	int		j;

	start_minimap(start, d->point.pos);
	i = -1;
	while (++i < BLOCK * MULTI)
	{
		j = -1;
		while (++j < BLOCK * MULTI)
		{
			idx[Y] = start[Y] + i / (double)MULTI;
			idx[X] = start[X] + j / (double)MULTI;
			if (idx[Y] > d->y_max - 1 || idx[X] > (int)ft_strlen(map[idx[Y]]))
				my_mlx_pixel_put(&d->minimap, j, i, 0xff5858);
			else if (map[idx[Y]][idx[X]] == '1')
				my_mlx_pixel_put(&d->minimap, j, i, 0x818181);
			else if (map[idx[Y]][idx[X]] == '0' || map[idx[Y]][idx[X]] == 'P')
				my_mlx_pixel_put(&d->minimap, j, i, 0xe8e8e8);
			else
				my_mlx_pixel_put(&d->minimap, j, i, 0xff5858);
		}
	}
	draw_player(d, start);
}

void	put_minimap(t_data *data, int minimap_x, int minimap_y)
{
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, \
			&data->minimap.bits_per_pixel, \
			&data->minimap.line_length, &data->minimap.endian);
	draw_minimap(data, data->map);
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
							data->minimap.img, minimap_x, minimap_y);
}
