/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:26:23 by ilko              #+#    #+#             */
/*   Updated: 2024/01/24 11:28:16 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	image[NORTH].addr = mlx_get_data_addr(image[NORTH].img, &image[NORTH].\
		bits_per_pixel, &image[NORTH].line_length, &image[NORTH].endian);
	image[SOUTH].addr = mlx_get_data_addr(image[SOUTH].img, &image[SOUTH].\
		bits_per_pixel, &image[SOUTH].line_length, &image[SOUTH].endian);
	image[WEST].addr = mlx_get_data_addr(image[WEST].img, &image[WEST].\
		bits_per_pixel, &image[WEST].line_length, &image[WEST].endian);
	image[EAST].addr = mlx_get_data_addr(image[EAST].img, &image[EAST].\
		bits_per_pixel, &image[EAST].line_length, &image[EAST].endian);
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
