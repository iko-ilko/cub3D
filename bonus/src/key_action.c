/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:32:26 by ilko              #+#    #+#             */
/*   Updated: 2024/02/03 16:44:00 by ilko             ###   ########.fr       */
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

void	vector_move(t_data *data, t_point *point, int move[4], t_vector *df)
{
	t_vector	temp;

	temp = vector_calculate(point->pos, *df, PLUS);
	if (data->map[(int)point->pos.y][(int)temp.x] == '1' || \
		move[WEST] == 0 || move[EAST] == 0)
	{
		if ((df->x < 0 && move[WEST] == 0) || (df->x >= 0 && move[EAST] == 0))
			point->pos.x = set_corrected_pos(data, move, X);
	}
	else
		point->pos.x += df->x;
	temp = vector_calculate(point->pos, *df, PLUS);
	if (data->map[(int)temp.y][(int)point->pos.x] == '1' || \
		move[NORTH] == 0 || move[SOUTH] == 0)
	{
		if ((df->y < 0 && move[NORTH] == 0) || (df->y >= 0 && move[SOUTH] == 0))
			point->pos.y = set_corrected_pos(data, move, Y);
	}
	else
		point->pos.y += df->y;
}

void	player_move(t_data *data, int key)
{
	int			change[4][2];
	int			i;
	int			move_index[4];
	t_vector	diff;

	diff = vector_normalizing(data->point.dir);
	diff = sight_rotate(diff, key);
	diff = vector_multiple(diff, 0.137);
	i = -1;
	while (++i < 4)
	{
		change[i][Y] = get_wall_index_y(i, data->point);
		change[i][X] = get_wall_index_x(i, data->point);
		if (data->map[change[i][Y]][change[i][X]] == '1' && \
			calculate_distance(data->point.pos, diff, i) == -1)
			move_index[i] = 0;
		else
			move_index[i] = 1;
	}
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
		put_minimap(data, 0, 0);
	}
	if (key == LEFT || key == RIGHT)
	{
		data->point.dir = vector_rotate(data->point.dir, (0.1 * \
		(key == LEFT) + -0.1 * (key == RIGHT)));
		data->point.plane = vector_rotate(data->point.plane, (0.1 * \
		(key == LEFT) + -0.1 * (key == RIGHT)));
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
		put_minimap(data, 0, 0);
	}
	return (SUCCESS);
}
