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

void	load_xpm_texture(t_pre_data *data, t_data *info, t_image image[4])
{
	int	w;
	int	h;

	sanitize_filename(data);
	image[NORTH].img = mlx_xpm_file_to_image(info->mlx, data->north_arv[1], \
		&image[NORTH].width, &image[NORTH].height);
	if (image[NORTH].img == NULL)
		exit_error(strerror(errno), "north texture");
	image[SOUTH].img = mlx_xpm_file_to_image(info->mlx, data->south_arv[1], \
		&image[SOUTH].width, &image[SOUTH].height);
	if (image[SOUTH].img == NULL)
		exit_error(strerror(errno), "south texture");
	image[WEST].img = mlx_xpm_file_to_image(info->mlx, data->west_arv[1], \
		&image[WEST].width, &image[WEST].height);
	if (image[WEST].img == NULL)
		exit_error(strerror(errno), "west texture");
	image[EAST].img = mlx_xpm_file_to_image(info->mlx, data->east_arv[1], \
		&image[EAST].width, &image[EAST].height);
	if (image[EAST].img == NULL)
		exit_error(strerror(errno), "east texture");
}

int	convert_rgb_int(char **rgb_str, char *line)
{
	int	i;
	int	res;
	int	temp;

	i = 0;
	res = 0;
	while (rgb_str[i] != NULL)
	{
		if (rgb_str[i][0] == '\n')
			exit_error(RGB_VALUE_ERROR, line);
		temp = my_atoi_cub(rgb_str[i]);
		if (temp < 0 || temp > 255)
			exit_error(RGB_VALUE_ERROR, line);
		res = res * 256 + temp;
		i++;
	}
	if (i != 3)
		exit_error(RGB_COUNT_ERROR, line);
	return (res);
}

void	convert_rgb(t_pre_data *data, t_data *map_info)
{
	char	**rgb_str;

	rgb_str = my_split(data->ceiling_arv[1], ",");
	map_info->ceiling_color = convert_rgb_int(rgb_str, data->ceiling_arv[1]);
	double_free(&rgb_str);

	rgb_str = my_split(data->floor_arv[1], ",");
	map_info->floor_color = convert_rgb_int(rgb_str, data->floor_arv[1]);
	double_free(&rgb_str);
}
