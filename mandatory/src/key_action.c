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
	// t_vector	change;

	// change = vector_normalizing(data->point.dir);
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
// 1사분면 오른쪽 벽면 up 키 누르면 여기 아래가 second로 가야하는데 왜 first로 가지?
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
//gap = (원래값 - 반올림한값)
//if gap > 0 && gap < 0.1   //or if gap < 0 == gap > -0.1
//내림값 += 0.1				//or 올림값 -= 0.1
void	set_correted_pos_wall(t_data *data, t_vector temp, t_vector change)
{
	t_vector	gap;

	if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
	{
		printf("Y\n");
		data->point.pos.x += change.x * 0.9;//비빌 때 속도. 와 간격(도 여기서 보정 되는듯)
		gap.y = data->point.pos.y - round(data->point.pos.y);//좌우키 다른 논리면 위에서 한번에 구하기
		if (gap.y > 0 && gap.y < 0.137)
			data->point.pos.y = floor(data->point.pos.y) + 0.137;
		printf("y done\n");
	}
	if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
	{
		printf("X\n");
		data->point.pos.y += change.y * 0.9;//비빌 때 속도. 와 간격(도 여기서 보정 되는듯)
		gap.x = data->point.pos.x - round(data->point.pos.x);//좌우키 다른 논리면 위에서 한번에 구하기
		if (gap.x < 0 && gap.x > 0.137)
			data->point.pos.x = ceil(data->point.pos.x) - 0.137;
	}

}
//각 무브의 맞닿는 벽을 체크하려고 하루를 썼지만 ....그냥 반올림해서 가까운데에 벽이 있으면 그 방향이 곧 보정할 값이 되네
//고민하던 벽과의 간격과 벽체크 한번에 될지도
void	set_corrected_pos(t_data *data, t_vector temp, t_vector change)
{
	t_vector gap;
	gap.y = data->point.pos.y - round(temp.y);
	gap.x = data->point.pos.x - round(temp.x);

	printf("gap x: %f gap y: %f\n", gap.x, gap.y);
	printf("temp x: %f temp y: %f\n", temp.x, temp.y);
	if ((gap.x > 0 && gap.x < 0.15) && data->map[(int)temp.y][(int)(temp.x - gap.x)] == '1') // 왼쪽 벽 체크
	{
		printf("1\n");
		data->point.pos.x = floor(data->point.pos.x) + 0.15;
		if (data->map[(int)(temp.y + gap.y)][(int)temp.x] == '0')
			data->point.pos.y += change.y * 0.9;
	}
	else if ((gap.x < 0 && gap.x > -0.15) && data->map[(int)temp.y][(int)(temp.x - gap.x)] == '1') // 오른쪽 벽 체크
	{
		printf("2\n");
		data->point.pos.x = ceil(data->point.pos.x) - 0.15;
		if (data->map[(int)(temp.y - gap.y)][(int)temp.x] == '0'){printf("!!\n");
			data->point.pos.y += change.y * 0.9;}
		// else
		// 	data->point.pos.y = ceil(data->point.pos.x) - 0.15;
	}
	else if ((gap.y > 0 && gap.y < 0.15) && data->map[(int)(temp.y - gap.y)][(int)temp.x] == '1') // 위쪽 벽 체크
	{
		printf("3\n");
		data->point.pos.y = floor(data->point.pos.y) + 0.15;
		if (data->map[(int)(temp.y)][(int)(temp.x + gap.x)] == '0')
			data->point.pos.x += change.x * 0.9;
	}
	else if ((gap.y < 0 && gap.y > -0.15) && data->map[(int)(temp.y - gap.y)][(int)temp.x] == '1') // 아래쪽 벽 체크
	{
		printf("4\n");
		data->point.pos.y = ceil(data->point.pos.y) - 0.15;
		if (data->map[(int)temp.y][(int)(temp.x + gap.x)] == '0')
			data->point.pos.x += change.x * 0.9;
	}
	else // 벽에 충돌하지 않는 경우
	{
		data->point.pos.x = temp.x;
		data->point.pos.y = temp.y;
	}
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
	// {// 살짝 각도틀고 앞 돌진하면 텍스쳐 너무 크게나옴. 아래 아예 값을 바꾸면 안될듯
		// set_correted_pos_wall(data, temp, change);
	// }
	// else
	// {//지금 설정할 논리가 정확하다면 위에 따로 벽이 아니라 0.137 안에 벽이 있다면 고정하고 아니면 temp...
		set_corrected_pos(data, temp, change);
		// data->point.pos.x = temp.x;
		// data->point.pos.y = temp.y;
	// }
}

int	ft_key_action(int key, t_data *data)
{printf("press: %d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
	printf("pre pos x: %f pre pos y: %f\n", data->point.pos.x, data->point.pos.y);
		player_move(data, key);
	printf("pos x: %f pos y: %f\n", data->point.pos.x, data->point.pos.y);
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
