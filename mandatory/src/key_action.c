/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:32:26 by ilko              #+#    #+#             */
/*   Updated: 2024/01/26 12:03:38 by ilko             ###   ########.fr       */
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
		return (vector_rotate(change, M_PI_2));
	else if (key == RIGHT)
		return (vector_rotate(change, -M_PI_2));
	return ((t_vector){0, 0});
}
/* 임시코드 */
int	check_wall(t_data *data, t_vector dir, t_vector temp)
{
	printf("-------------x:%f    y:%f\n", dir.x, dir.y);
	if (dir.x < 0 && dir.y > 0)//x:- y:+////
	{
		if (data->map[(int)(temp.y + 0.2)][(int)(temp.x - 0.2)] == '1')
			return (-1);
	}
	else if (dir.x > 0 && dir.y > 0)//x:+ y:-////
	{
		if (data->map[(int)(temp.y + 0.2)][(int)(temp.x + 0.2)] == '1')
			return (-1);
	}
	else if (dir.x > 0 && dir.y < 0)//x:+ y:////
	{
		if (data->map[(int)(temp.y - 0.2)][(int)(temp.x + 0.2)] == '1')
			return (-1);
	}
	else if (dir.x < 0 && dir.y < 0)//x:- y:+////
	{
		if (data->map[(int)(temp.y - 0.2)][(int)(temp.x - 0.2)] == '1')
			return (-1);
	}
	printf("temp x:%f temp:%f\n", temp.x, temp.y);
	return (0);
}

void	player_move(t_data *data, int key)
{
	t_vector	change;
	t_vector	temp;

	temp.x = data->point.pos.x;
	temp.y = data->point.pos.y;
	change = vector_normalizing(data->point.dir);
	change = sight_rotate(change, key);
	change = vector_multiple(change, 0.137);//0.137
	temp = vector_calculate(data->point.pos, change, PLUS);
	if (data->map[(int)temp.y][(int)temp.x] == '1')
	{//벽 미끄러짐 여기 5줄만 주석 풀고 테스트해보셔요
		// change = vector_normalizing(data->point.dir);
		// if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
		// 	data->point.pos.x += change.x * 0.137;
		// if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
		// 	data->point.pos.y += change.y * 0.137;
		return ;
	}
	// if (check_wall(data, data->point.dir, temp) == -1)
	// 	return ;//이걸로 플레이어와 벽 의 간격을 줄라했음.
	data->point.pos.x = temp.x;
	data->point.pos.y = temp.y;
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
		data->point.dir = vector_rotate(data->point.dir, (0.1 * (key == A) \
		+ -0.1 * (key == D)));
		data->point.plane = vector_rotate(data->point.plane, (0.1 * (key == A) \
		+ -0.1 * (key == D)));
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
	}
	printf("dir x: %f dir y: %f\n", data->point.dir.x, data->point.dir.y);
	printf("pos x: %f pos y: %f\n------\n", data->point.pos.x, data->point.pos.y);
	return (SUCCESS);
}
