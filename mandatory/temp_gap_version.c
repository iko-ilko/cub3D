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

int	calculate_distance(t_vector pos, t_vector diff, int i)
{
	printf("diff x %f diff y%f\n", diff.x, diff.y);
	if (i == NORTH)
	{
		if (ft_abs(pos.y + diff.y - floor(pos.y)) < 0.1)
			return (-1);
	}
	if (i == SOUTH)
	{
		printf("---%f\n", 1 - pos.y + diff.y - floor(pos.y));
		if (ft_abs(pos.y + diff.y - ceil(pos.y)) < 0.1)
			return (-1);
	}
	if (i == EAST)
	{
		if (ft_abs(pos.x + diff.x - ceil(pos.x)) < 0.1)
			return (-1);
	}
	if (i == WEST)
	{
		if (ft_abs(pos.x + diff.x - floor(pos.x)) < 0.1)
			return (-1);
	}
	return (1);
}
double	set_corrected_pos(t_data *d, t_vector diff, int move_i[4], int flag)
{(void)diff;
	if (move_i[NORTH] == 0 && flag == Y)
	{
		printf("north\n");
		return (floor(d->point.pos.y) + 0.1);
	}
	if (move_i[SOUTH] == 0 && flag == Y)
	{
		printf("south\n");
		return (ceil(d->point.pos.y) - 0.1);
	}
	if (move_i[WEST] == 0 && flag == X)
	{
		printf("west\n");
		return (floor(d->point.pos.x) + 0.1);
	}
	if (move_i[EAST] == 0 && flag == X)
	{
		printf("east\n");
		return (ceil(d->point.pos.x) - 0.1);
	}

	return (0);
	// printf("f: %d\n", f);
	// if (f == X + Y + 1)
	// {
	// 	d->point.pos.x += diff.x;
	// 	d->point.pos.y += diff.y;
	// }
	// else if (f == Y)
	// {
	// 	printf("Y\n");
	// 	if (move_i[NORTH] == 0)
	// 		d->point.pos.y = floor(d->point.pos.y + diff.y) + 0.1;
	// 	else if (move_i[SOUTH] == 0)
	// 		d->point.pos.y = ceil(d->point.pos.y + diff.y) - 0.1;
	// 	d->point.pos.x += diff.x;
	// }
	// else if (f == X)
	// {
	// 	printf("X\n");
	// 	if (move_i[WEST] == 0)
	// 		d->point.pos.x = floor(d->point.pos.x + diff.x) + 0.1;
	// 	else if (move_i[EAST] == 0)
	// 		d->point.pos.x = ceil(d->point.pos.x + diff.x) - 0.1;
	// 	d->point.pos.y += diff.y;
	// }
}

void	vector_move(t_data *data, t_point *point, int move_index[4], t_vector *diff)
{
	t_vector	temp;

	// X축 이동
	temp = vector_calculate(point->pos, *diff, PLUS);
	if (diff->x != 0) {
		if (data->map[(int)point->pos.y][(int)temp.x] == '1' || move_index[WEST] == 0 || move_index[EAST] == 0) // X축 이동이 벽에 부딪히는 경우
		{
				printf("?\n");
			if (diff->x < 0 && move_index[WEST] == 0)
			{
				point->pos.x = set_corrected_pos(data, *diff, move_index, X);
			}
			else if (diff->x >= 0 && move_index[EAST] == 0)
			{
				point->pos.x = set_corrected_pos(data, *diff, move_index, X);
			}
		}
		else
		{
			point->pos.x += diff->x;
		}
	}
	
	// Y축 이동
	temp = vector_calculate(point->pos, *diff, PLUS);
	if (diff->y != 0) {
		if (data->map[(int)temp.y][(int)point->pos.x] == '1' || move_index[NORTH] == 0 || move_index[SOUTH] == 0) // Y축 이동이 벽에 부딪히는 경우
		{
				printf("???\n");
			if (diff->y < 0 && move_index[NORTH] == 0)
			{printf("1\n");
				point->pos.y = set_corrected_pos(data, *diff, move_index, Y);
			}
			else if (diff->y >= 0 && move_index[SOUTH] == 0)
			{printf("2\n");
				point->pos.y = set_corrected_pos(data, *diff, move_index, Y);
			}
		}
		else
		{
			point->pos.y += diff->y;
		}
	}
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
		printf("%d: %d\n", i, move_index[i]);
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
	printf("pos x:%f pos y:%f\n", data->point.pos.x, data->point.pos.y);
	return (SUCCESS);
}

모서리 부분도 간격 잘 되지만 한번 깊게 들어가서 화면 크게 나오는 버전.
지금 버전이 안되면 이 버전으로 제출.