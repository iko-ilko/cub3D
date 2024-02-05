/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:18:42 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 16:30:38 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	get_wall_index_x(int i, t_point point)
{
	int	res;

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
	int	res;

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
	if (i == NORTH)
	{
		if (ft_abs(pos.y + diff.y - floor(pos.y)) < 0.1)
			return (-1);
	}
	if (i == SOUTH)
	{
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

double	set_corrected_pos(t_data *d, int move_i[4], int flag)
{
	if (move_i[NORTH] == 0 && flag == Y)
		return (floor(d->point.pos.y) + 0.1);
	if (move_i[SOUTH] == 0 && flag == Y)
		return (ceil(d->point.pos.y) - 0.1);
	if (move_i[WEST] == 0 && flag == X)
		return (floor(d->point.pos.x) + 0.1);
	if (move_i[EAST] == 0 && flag == X)
		return (ceil(d->point.pos.x) - 0.1);
	return (0);
}
