#include "../include/cub3d.h"

void	sanitize_filename(t_pre_data *pre)
{
	int	i;

	i = -1;
	while (pre->north_arv[1][++i])
		if (pre->north_arv[1][i] == '\n')
			pre->north_arv[1][i] = '\0';
	i = -1;
	while (pre->south_arv[1][++i])
		if (pre->south_arv[1][i] == '\n')
			pre->south_arv[1][i] = '\0';
	i = -1;
	while (pre->west_arv[1][++i])
		if (pre->west_arv[1][i] == '\n')
			pre->west_arv[1][i] = '\0';
	i = -1;
	while (pre->east_arv[1][++i])
		if (pre->east_arv[1][i] == '\n')
			pre->east_arv[1][i] = '\0';
}

void	load_xpm_texture(t_pre_data *pre, t_data *data, t_image image[4])
{
	int	w;
	int	h;

	sanitize_filename(pre);
	image[NORTH].img = mlx_xpm_file_to_image(data->mlx, pre->north_arv[1], \
		&image[NORTH].width, &image[NORTH].height);
	if (image[NORTH].img == NULL)
		exit_error(strerror(errno), "north texture");
	image[SOUTH].img = mlx_xpm_file_to_image(data->mlx, pre->south_arv[1], \
		&image[SOUTH].width, &image[SOUTH].height);
	if (image[SOUTH].img == NULL)
		exit_error(strerror(errno), "south texture");
	image[WEST].img = mlx_xpm_file_to_image(data->mlx, pre->west_arv[1], \
		&image[WEST].width, &image[WEST].height);
	if (image[WEST].img == NULL)
		exit_error(strerror(errno), "west texture");
	image[EAST].img = mlx_xpm_file_to_image(data->mlx, pre->east_arv[1], \
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

void	convert_rgb(t_pre_data *pre, t_data *data)
{
	char	**rgb_str;

	rgb_str = my_split(pre->ceiling_arv[1], ",");
	data->ceiling_color = convert_rgb_int(rgb_str, pre->ceiling_arv[1]);
	double_free(&rgb_str);

	rgb_str = my_split(pre->floor_arv[1], ",");
	data->floor_color = convert_rgb_int(rgb_str, pre->floor_arv[1]);
	double_free(&rgb_str);
}
