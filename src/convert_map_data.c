#include "../include/cub3d.h"

void	sanitize_filename(t_pre_data *data)
{
	int	i;

	i = -1;
	while (data->north_arv[1][++i])
		if (data->north_arv[1][i] == '\n')
			data->north_arv[1][i] = '\0';
	i = -1;
	while (data->south_arv[1][++i])
		if (data->south_arv[1][i] == '\n')
			data->south_arv[1][i] = '\0';
	i = -1;
	while (data->west_arv[1][++i])
		if (data->west_arv[1][i] == '\n')
			data->west_arv[1][i] = '\0';
	i = -1;
	while (data->east_arv[1][++i])
		if (data->east_arv[1][i] == '\n')
			data->east_arv[1][i] = '\0';
}

void	load_xpm_texture(t_pre_data *data, t_map_info *map)
{
	int	w;
	int	h;

	sanitize_filename(data);
	map->north = mlx_xpm_file_to_image(map->mlx, data->north_arv[1], &w, &h);
	if (map->north == NULL)
		exit_error(strerror(errno), "north texture");

	map->south = mlx_xpm_file_to_image(map->mlx, data->south_arv[1], &w, &h);
	if (map->south == NULL)
		exit_error(strerror(errno), "south texture");

	map->west = mlx_xpm_file_to_image(map->mlx, data->west_arv[1], &w, &h);
	if (map->west == NULL)
		exit_error(strerror(errno), "west texture");

	map->east = mlx_xpm_file_to_image(map->mlx, data->east_arv[1], &w, &h);
	if (map->east == NULL)
		exit_error(strerror(errno), "east texture");
}

int		convert_rgb_int(char **rgb_str)
{
	int	i;
	int	res;
	int	temp;

	i = 0;
	res = 0;
	while (rgb_str[i] != NULL)
	{
		temp = my_atoi(rgb_str[i]);
		if (temp < 0 || temp > 255)
			exit_error(RGB_VALUE_ERROR, NULL);
		res = res * 256 + temp;
		i++;
	}
	if (i != 3)
		exit_error(RGB_COUNT_ERROR, NULL);
	return (res);
}

void	convert_rgb(t_pre_data *data, t_map_info *map_info)
{
	char	**rgb_str;

	rgb_str = ft_split(data->ceiling_color_arv[1], ",");
	map_info->ceiling_color = convert_rgb_int(rgb_str);
	free_double(&rgb_str);

	rgb_str = ft_split(data->floor_color_arv[1], ",");
	map_info->floor_color = convert_rgb_int(rgb_str);
	free_double(&rgb_str);

}