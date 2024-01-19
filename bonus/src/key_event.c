# include "../include/cub3d.h"


int	press_key(int key, t_data *data)
{
	if (key == W || key == UP)
		data->move_p[NORTH] = 1;
	if (key == S || key == DOWN)
		data->move_p[SOUTH] = 1;
	if (key == A || key == LEFT)
		data->move_p[WEST] = 1;
	if (key == D || key == RIGHT)
		data->move_p[EAST] = 1;
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	ray_casting(data);
	return (0);
}

int	release_key(int key, t_data *data)
{
	if (key == W || key == UP)
		data->move_p[NORTH] = 0;
	if (key == S || key == DOWN)
		data->move_p[SOUTH] = 0;
	if (key == A || key == LEFT)
		data->move_p[WEST] = 0;
	if (key == D || key == RIGHT)
		data->move_p[EAST] = 0;
	return (0);
}

int	check_wall(t_data *data, char **map, double p_x, double p_y)
{
	int	pos[2];

	pos[X] = (int)p_x;
	pos[Y] = (int)p_y;
	if (map[pos[Y]][pos[X]] == '1')
		return (0);
	return (1);
}

void	check_move(t_data *data)
{
	if (data->move_p[NORTH] == 1)
	{
		data->point.player.y -= STEP;
		if (check_wall(data, data->map, data->point.player.x, data->point.player.y) == 0)
			data->point.player.y += STEP;
	}
	if (data->move_p[SOUTH] == 1)
	{
		data->point.player.y += STEP;
		if (check_wall(data, data->map, data->point.player.x, data->point.player.y) == 0)
			data->point.player.y -= STEP;
	}
	if (data->move_p[WEST] == 1)
	{
		data->point.player.x -= STEP;
		if (check_wall(data, data->map, data->point.player.x, data->point.player.y) == 0)
			data->point.player.x += STEP;
	}
	if (data->move_p[EAST] == 1)
	{
		data->point.player.x += STEP;
		if (check_wall(data, data->map, data->point.player.x, data->point.player.y) == 0)
			data->point.player.x -= STEP;
	}
}
