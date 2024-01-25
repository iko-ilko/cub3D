/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:32:26 by ilko              #+#    #+#             */
/*   Updated: 2024/01/25 20:34:07 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vector	sight_rotate(t_vector change, int key)
{
	if (key == UP)
		return (change);
	else if (key == DOWN)
		return (vector_multiple(change, -1));
	else if (key == LEFT)
		return (vector_rotate(change, -M_PI_2));
	else if (key == RIGHT)
		return (vector_rotate(change, M_PI_2));
	return ((t_vector){0, 0});
}

void	player_move(t_data *data, int key)
{
	t_vector	change;
	t_vector	temp;

	temp.x = data->point.pos.x;
	temp.y = data->point.pos.y;
	change = vector_normalizing(data->point.dir);
	change = sight_rotate(change, key);
	change = vector_multiple(change, 0.1);
	temp = vector_calculate(data->point.pos, vector_multiple(change, 2), PLUS);
	if (data->map[(int)temp.y][(int)temp.x] == '1')
		return ;
	temp = vector_calculate(data->point.pos, vector_multiple(change, 6), PLUS);
	if (data->map[(int)temp.y][(int)temp.x] == '1')
		return ;
	data->point.pos = vector_calculate(data->point.pos, change, PLUS);
}

int	ft_key_action(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		player_move(data, key);
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
	}
	if (key == A || key == D)
	{
		data->point.dir = vector_rotate(data->point.dir, (-0.2 * (key == A) \
							+ 0.2 * (key == D)));
		data->point.plane = vector_rotate(data->point.plane, (-0.2 * (key == A) \
							+ 0.2 * (key == D)));
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
	}
	return (SUCCESS);
}
