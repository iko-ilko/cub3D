/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:32:26 by ilko              #+#    #+#             */
/*   Updated: 2024/01/29 23:19:58 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_vector	sight_rotate(t_vector change, int key)
{
	if (key == W)
		return (change);
	else if (key == S)
		return (vector_multiple(change, -1));
	else if (key == A)
		return (vector_rotate(change, M_PI_2));
	else if (key == D)
		return (vector_rotate(change, -M_PI_2));
	return ((t_vector){0, 0});
}
int	get_wall_index_x(int i, t_point point)
{
	int res;

	if (i == NORTH)
		res = (int)point.pos.x;
	else if (i == SOUTH)
		res = (int)point.pos.x;
	else if (i == EAST)
		res = (int)point.pos.x + 1;
	else
		res = (int)point.pos.x - 1;
	return (res);
}

int	get_wall_index_y(int i, t_point point)
{
	int res;

	if (i == NORTH)
		res = (int)point.pos.y - 1;
	else if (i == SOUTH)
		res = (int)point.pos.y + 1;
	else if (i == EAST)
		res = (int)point.pos.y;
	else
		res = (int)point.pos.y;
	return (res);
}	

int	calculate_distance(t_vector pos, int i)
{
	if (i == NORTH)
	{
		if (ft_abs(pos.y - floor(pos.y)) < 0.137)
			return (-1);
	}
	if (i == SOUTH)
	{
		if (ft_abs(1 - pos.y + floor(pos.y)) < 0.137)
			return (-1);
	}
	if (i == EAST)
	{
		if (ft_abs(1 - pos.x + floor(pos.x)) < 0.137)
			return (-1);
	}
	if (i == WEST)
	{
		if (ft_abs(pos.x - floor(pos.x)) < 0.137)
			return (-1);
	}
	return (1);
}

void	vector_move(t_data *data, t_point *point, int move_index[4], t_vector *diff)
{
	t_vector	temp;

	if (move_index[NORTH] == 0 && diff->y < 0)
		diff->y = 0;
	else if (move_index[SOUTH] == 0 && diff->y >= 0)
		diff->y = 0;
	if (move_index[WEST] == 0 && diff->x < 0)
		diff->x = 0;
	else if (move_index[EAST] == 0 && diff->x >= 0)
		diff->x = 0;
	temp.x = data->point.pos.x + diff->x;
	temp.y = data->point.pos.y + diff->y;
	if ((int)temp.x != (int)point->pos.x && (int)temp.y != (int)point->pos.y \
		&& data->map[(int)temp.y][(int)temp.x] == '1')
				return;
	point->pos.y += diff->y;
	point->pos.x += diff->x;
}

void	player_move(t_data *data, int key)
{
	int			change[4][2];
	int			i;
	int			move_index[4];
	t_vector	diff;

	i = -1;
	while (++i < 4)
	{
		change[i][Y] = get_wall_index_y(i, data->point);
		change[i][X] = get_wall_index_x(i, data->point);
		if (data->map[change[i][Y]][change[i][X]] == '1' && \
			calculate_distance(data->point.pos, i) == -1)
			move_index[i] = 0;
		else
			move_index[i] = 1;
	}
	diff = vector_normalizing(data->point.dir);
	diff = sight_rotate(diff, key);
	diff = vector_multiple(diff, 0.137);
	vector_move(data, &data->point, move_index, &diff);
}

int	ft_key_action(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (key == W || key == S || key == A || key == D)
	{
		player_move(data, key);
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
	}
	if (key == LEFT || key == RIGHT)
	{
		data->point.dir = vector_rotate(data->point.dir, (0.1 * \
		(key == LEFT) + -0.1 * (key == RIGHT)));
		data->point.plane = vector_rotate(data->point.plane, (0.1 * \
		(key == LEFT) + -0.1 * (key == RIGHT)));
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
	}
	return (SUCCESS);
}
