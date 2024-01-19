# include "../../include/cub3d.h"

void	start_minimap(t_data *data, double start[2], t_vector player_pos)
{
	int		offset;

	offset = (BLOCK_MAX - 1) / 2;
	start[Y] = player_pos.y - offset;
	start[X] = player_pos.x - offset;
	if (player_pos.y - offset < 0) //나중에 최적화를 위해 매크로 연산된 값이 아닌 상수값으로 변경 될 수 있음.
		start[Y] = 0;
	if (player_pos.x - offset < 0)
		start[X] = 0;
}

void	draw_player(t_data *data, char **map, t_image *minimap, double start[2])
{
	int	p_pos[2];
	int	i;
	int	j;

	p_pos[Y] = (int)((data->point.player.y - start[Y]) * (double)MULTIPLE);
	p_pos[X] = (int)((data->point.player.x - start[X]) * (double)MULTIPLE);
	i = -1;
	while (++i < MULTIPLE)
	{
		j = -1;
		while (++j < MULTIPLE)
			my_mlx_pixel_put(&data->minimap, j + p_pos[X], i + p_pos[Y], 0x65a2ff);
	}
}
//player 그리는건 나중에 형이 다 완성하면 맞게 수정하자 
void	draw_minimap(t_data *data, char **map, t_image *minimap)
{
	double	start[2];
	int		map_idx[2];
	int		i;
	int		j;

	start_minimap(data, start, data->point.player);
	i = -1;
	while (++i < BLOCK_MAX * MULTIPLE)
	{
		j = -1;
		while (++j < BLOCK_MAX * MULTIPLE)
		{
			map_idx[Y] = start[Y] + i / (double)MULTIPLE;
			map_idx[X] = start[X] + j / (double)MULTIPLE;
			if (map_idx[Y] > data->y_max - 1 || map_idx[X] > ft_strlen(map[map_idx[Y]]))
				my_mlx_pixel_put(&data->minimap, j, i, 0xff5858);
			else if (map[map_idx[Y]][map_idx[X]] == '1')
				my_mlx_pixel_put(&data->minimap, j, i, 0x5f5f5f);
			else if (map[map_idx[Y]][map_idx[X]] == '0' || map[map_idx[Y]][map_idx[X]] == 'P')
				my_mlx_pixel_put(&data->minimap, j, i, 0xe8e8e8);
			else
				my_mlx_pixel_put(&data->minimap, j, i, 0xff5858);
		}
	}
	draw_player(data, data->map, data->minimap.img, start);
}


void	put_minimap(t_data *data, int minimap_x, int minimap_y)
{
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bits_per_pixel, &data->minimap.line_length, &data->minimap.endian);
	draw_minimap(data, data->map, data->minimap.img);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->minimap.img, minimap_x, minimap_y);
}