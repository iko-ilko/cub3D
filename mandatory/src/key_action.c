/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 20:32:26 by ilko              #+#    #+#             */
/*   Updated: 2024/01/29 03:08:02 by ilko             ###   ########.fr       */
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

void	set_move_dda(t_vector temp, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (temp.x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - temp.x) \
							* ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (temp.y - ray->map_y) \
							* ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - temp.y) \
							* ray->deltadist_y;
	}
}

void	move_perform_dda(t_ray *ray)
{

	if (ray->sidedist_x < ray->sidedist_y)
	{
		ray->sidedist_x += ray->deltadist_x;
		ray->map_x += ray->step_x;
		// ray->side = 0;
	}
	else
	{
		ray->sidedist_y += ray->deltadist_y;
		ray->map_y += ray->step_y;
		// ray->side = 1;
	}
	// ray->sidedist_x += 1;
	// ray->sidedist_y += 1;
}

void	init_move_ray_dir(t_data *data, t_ray *ray, t_vector *dir, int key, t_vector temp)
{
	// int	i;

	if (key == W)
		*dir = vector_rotate(data->point.dir, deg_to_rad(0));
	else if (key == A)
		*dir = vector_rotate(data->point.dir, deg_to_rad(90));
	else if (key == S)
		*dir = vector_rotate(data->point.dir, deg_to_rad(180));
	else if (key == D)
		*dir = vector_rotate(data->point.dir, deg_to_rad(270));
	ray->camera_x = 0;
	ray->dir_x = dir->x;
	ray->dir_y = dir->y;
	ray->map_x = (int)temp.x;
	ray->map_y = (int)temp.y;
	printf("%d %d %f %f %d %d\n", (int)temp.x, (int)temp.y, temp.x, temp.y, ray->map_x, ray->map_y);
	// ray->map_y = (int)data->point.pos.y;
	// ray->map_y = (int)data->point.pos.y;
	ray->deltadist_x = fabs(1 / ray->dir_x) / 10;// /10은 임임시  
	ray->deltadist_y = fabs(1 / ray->dir_y) / 10;
	// i = 0;
	// for (int j = 0; j < 4; j++)
	// 	dir[j] = vector_rotate(data->point.dir, deg_to_rad(90 * j)); 
	// while (i < 4)
	// {
	// 	ray[i].camera_x = 0;
	// 	ray[i].dir_x = dir[i].x;
	// 	ray[i].dir_y = dir[i].y;
	// 	ray[i].map_x = (int)data->point.pos.x;
	// 	ray[i].map_y = (int)data->point.pos.y;
	// 	ray[i].deltadist_x = fabs(1 / ray[i].dir_x) / 10;// /10은 임임시  
	// 	ray[i].deltadist_y = fabs(1 / ray[i].dir_y) / 10;
	// 	i++;
	// }
}
int	check_wall(t_data *data, t_vector temp, int key)
{
	t_vector	dir;
	t_ray		ray;
	// double		min[4];
	// int			i;

	init_move_ray_dir(data, &ray, &dir, key, temp);
	printf("ray map x:%d y:%d\n", ray.map_y, ray.map_x);
	// i = 0;
	printf("---------\n");
	// if (key == W)
	// {
		set_move_dda(temp, &ray);
		move_perform_dda(&ray);
	// }
	// else if (key == A)
	// {
	// 	set_move_dda(temp, &ray);
	// 	move_peform_dda(&ray);
	// }
	// else if (key == S)
	// {
	// 	set_move_dda(temp, &ray);
	// 	move_peform_dda(&ray);
	// }
	// else if (key == D)
	// {
	// 	set_move_dda(temp, &ray);
	// 	move_peform_dda(&ray);
	// }
	printf("ray map x:%d y:%d\n", ray.map_y, ray.map_x);
	if (data->map[ray.map_y][ray.map_x] == '1')
		return (-1);
	printf("---------\n");
	// if (data->map[ray->map_y][ray->map_x] > '0')
	// printf("min: %f\n", min[0]);
	return (0);
}
void	set_corrected_pos(t_data *data, t_vector temp)
{
	t_vector gap;
	gap.y = temp.x - round(temp.x);
	gap.x = temp.y - round(temp.y);

	printf("gap x: %f gap y: %f\n", gap.x, gap.y);
	printf("temp x: %f temp y: %f\n", temp.x, temp.y);
	if ((gap.x > 0 && gap.x < 0.15) && data->map[(int)temp.y][(int)(temp.x - gap.x)] == '1') // 왼쪽 벽 체크
	{
		printf("1\n");
		data->point.pos.x = floor(data->point.pos.x) + 0.15;
	}
	else if ((gap.x < 0 && gap.x >= -0.15)) //
	{
		printf("2\n");
		data->point.pos.y = floor(data->point.pos.y) + 0.1;
	}
	else if ((gap.y > 0 && gap.y < 0.15) && data->map[(int)(temp.y - gap.y)][(int)temp.x] == '1') // 위쪽 벽 체크
	{
		printf("3\n");
		data->point.pos.y = floor(data->point.pos.y) + 0.15;
	}
	else if ((gap.y < 0 && gap.y > -0.15) && data->map[(int)(temp.y - gap.y)][(int)temp.x] == '1') // 아래쪽 벽 체크
	{
		printf("4\n");
		data->point.pos.y = ceil(data->point.pos.y) - 0.15;
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
	// if (check_wall(data, temp, key) == -1)
	// {
	// 	set_corrected_pos(data, temp, change);
	// 	if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
	// 		data->point.pos.x += change.x * 0.9;
	// 	if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
	// 		data->point.pos.y += change.y * 0.9;
	// }

	if (data->map[(int)data->point.pos.y][(int)temp.x] == '0')
	{printf("?\n");
		data->point.pos.x = temp.x;
		if (data->map[(int)temp.y][(int)data->point.pos.x] == '1')
			set_corrected_pos(data, temp);
	}

	if (data->map[(int)temp.y][(int)data->point.pos.x] == '0')
	{printf("??\n");
		data->point.pos.y = temp.y;
		if (data->map[(int)data->point.pos.y][(int)temp.x] == '1')
			set_corrected_pos(data, temp);
	}
	// else
	// {
	// data->point.pos.x = temp.x;
	// data->point.pos.y = temp.y;
	// }
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
		data->point.dir = vector_rotate(data->point.dir, (0.1 * (key == LEFT) \
		+ -0.1 * (key == RIGHT)));
		data->point.plane = vector_rotate(data->point.plane, (0.1 * (key == LEFT) \
		+ -0.1 * (key == RIGHT)));
		mlx_clear_window(data->mlx, data->mlx_win);
		ray_casting(data);
	}
	printf("dir x: %f dir y: %f\n", data->point.dir.x, data->point.dir.y);
	printf("pos x: %f pos y: %f\n------\n", data->point.pos.x, data->point.pos.y);
	return (SUCCESS);
}
