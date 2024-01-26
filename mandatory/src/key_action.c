/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:32:26 by ilko              #+#    #+#             */
/*   Updated: 2024/01/26 17:31:09 by ilko             ###   ########.fr       */
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
void	change_dir_check_wall(t_vector *dist, int quad, int key)
{
	if (quad == 1)
	{
		if (key == UP)
		{
			dist->x *= -1;
			dist->y *= -1;
		}
		else if (key == DOWN)
			;
		else if (key == LEFT)
			dist->x *= -1;
		else if (key == RIGHT)
			dist->y *= -1;
	}
	else if (quad == 2)
	{
		if (key == LEFT || key == DOWN)
			dist->x *= -1;
		else if (key == RIGHT)
			dist->y *= -1;
	}
	else if (quad == 3)
	{
		// if (key == RIGHT || key == DOWN)
		// 	dist->x *= -1;
		// else if (key == LEFT)
		// 	dist->y *= -1;
	}
}

/* 임시코드 */
int	check_wall(t_data *data, t_vector dir, t_vector temp, int key)
{
	t_vector	dist;
	t_vector	change;

	change = vector_normalizing(data->point.dir);
	dist.x = 0.137;
	dist.y = 0.137;
	printf("-------------x:%f    y:%f\n", dir.x, dir.y);
	(void)key;
	if (dir.x < 0 && dir.y < 0)//x:- y:-////map기준 1사분면
	{
		printf("1\n");
		change_dir_check_wall(&dist, 1, key);
		//여기서 나누자 
		// if (data->map[(int)(temp.y - dist.y)][(int)(temp.x - dist.x)] == '1')//이거 나눠야 할지 체크
1사분면 오른쪽 벽면 up 키 누르면 여기 아래가 second로 가야하는데 왜 first로 가지?
		if (data->map[(int)(data->point.pos.y + dist.y)][(int)(temp.x + dist.x)] == '1'){printf("first\n");
			return (-1);}
		else if (data->map[(int)(temp.y + dist.y)][(int)(data->point.pos.x + dist.x)] == '1'){printf("second\n");
			return (-2);}
	}
	else if (dir.x >= 0 && dir.y < 0)//x:+ y:-////map기준 2사분면
	{
		printf("2\n");
	// change_dir_check_wall(&dist, 2, key);
		if (data->map[(int)(temp.y - dist.y)][(int)(temp.x + dist.x)] == '1')
			return (-1);
	}
	else if (dir.x >= 0 && dir.y >= 0)//x:+ y:+////map기준 3사분면
	{
		printf("3\n");
	// change_dir_check_wall(&dist, 3, key);
		if (data->map[(int)(temp.y + dist.y)][(int)(temp.x + dist.x)] == '1')
			return (-1);
	}
	else if (dir.x < 0 && dir.y > 0)//x:- y:+////map기준 4사분면
	{
		printf("4\n");
	// change_dir_check_wall(&dist, 4, key);
		if (data->map[(int)(temp.y + dist.y)][(int)(temp.x - dist.x)] == '1')
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
	// if (data->map[(int)temp.y][(int)temp.x] == '1')
	// {//벽 미끄러짐 여기 5줄만 주석 풀고 테스트해보셔요
	// 	// if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
	// 	// 	data->point.pos.x += change.x * 0.137;//배수 + 0.2 위치에 고정시키기
	// 	// if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
	// 	// 	data->point.pos.y += change.y * 0.137;
	// 	if (data->map[(int)data->point.pos.y][(int)temp.x] == '1')
	// 	{
	// 		data->point.pos.x = temp.x;
	// 		data->point.pos.y = (int)temp.y + 0.2;
	// 	}
	// 	if (data->map[(int)temp.y][(int)data->point.pos.x] == '1')
	// 	{
	// 		printf("%f\n", (int)data->point.pos.x + 0.2);
	// 		data->point.pos.x = (int)data->point.pos.x + 0.2;
	// 		data->point.pos.y = temp.y;
	// 	}
	// }
	// if (check_wall(data, data->point.dir, temp, key) == -1)
	// {//벽 미끄러짐 여기 5줄만 주석 풀고 테스트해보셔요
	// 	if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
	// 	{
	// 		if (key == RIGHT)
	// 			data->point.pos.x -= change.x * 0.137;//이 값때문에 반대로 미끄러지는 경우 있어서 분기 나눠야할듯
	// 		else if (key == DOWN)
	// 			data->point.pos.x += change.x * 0.137;//이 값때문에 반대로 미끄러지는 경우 있어서 분기 나눠야할듯
	// 		printf("??????\n");
	// 	}
	// 	if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
	// 	{
	// 		if (key == LEFT)
	// 			data->point.pos.y -= change.y * 0.137;
	// 		else if (key == UP)
	// 			data->point.pos.y += change.y * 0.137;
	// 	}
	// }
	int test = check_wall(data, data->point.dir, temp, key);
	if (test == -1)
	{//벽 미끄러짐 여기 5줄만 주석 풀고 테스트해보셔요
		if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
		{
			if (key == RIGHT)
				data->point.pos.x -= change.x * 0.137;//이 값때문에 반대로 미끄러지는 경우 있어서 분기 나눠야할듯
			else if (key == DOWN)
				data->point.pos.x += change.x * 0.137;//이 값때문에 반대로 미끄러지는 경우 있어서 분기 나눠야할듯
		}

	}
	else if (test == -2)
	{
		if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
		{
			if (key == LEFT)
				data->point.pos.y -= change.y * 0.137;
			else if (key == UP)
				data->point.pos.y += change.y * 0.137;
		}
	}
	else
	{
	data->point.pos.x = temp.x;
	data->point.pos.y = temp.y;
	}
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
	// printf("dir x: %f dir y: %f\n", data->point.dir.x, data->point.dir.y);
	printf("pos x: %f pos y: %f\n------\n", data->point.pos.x, data->point.pos.y);
	return (SUCCESS);
}
