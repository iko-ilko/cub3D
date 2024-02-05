/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:17:27 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 16:28:08 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"
#include "../include/get_next_line.h"

int	get_map_info(t_pre_data *pre, char *line)
{
	char	**arv;

	if (line[0] == '\n')
		return (-1);
	arv = my_split(line, " ");
	if (arv[0] == NULL || arv[1] == NULL || arv[2] != NULL)
		exit_error(MAP_INFO_LINE_ERROR, line);
	if (my_strcmp("NO", arv[0]) == 0 && pre->north_arv == NULL)
		pre->north_arv = arv;
	else if (my_strcmp("SO", arv[0]) == 0 && pre->south_arv == NULL)
		pre->south_arv = arv;
	else if (my_strcmp("WE", arv[0]) == 0 && pre->west_arv == NULL)
		pre->west_arv = arv;
	else if (my_strcmp("EA", arv[0]) == 0 && pre->east_arv == NULL)
		pre->east_arv = arv;
	else if (my_strcmp("F", arv[0]) == 0 && pre->floor_arv == NULL)
		pre->floor_arv = arv;
	else if (my_strcmp("C", arv[0]) == 0 && pre->ceiling_arv == NULL)
		pre->ceiling_arv = arv;
	else
		exit_error(MAP_INFO_LINE_ERROR, line);
	return (0);
}

void	make_map_space(t_pre_data *pre, int offset)
{
	int		fd;
	int		map_line_cnt;
	char	*line;

	fd = open(pre->cub_file_name, O_RDONLY);
	if (fd == -1)
		exit_error(OPEN_ERROR, pre->cub_file_name);
	map_line_cnt = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (offset <= 0)
			map_line_cnt++;
		single_free(&line);
		offset--;
	}
	pre->data->map = malloc(sizeof(char *) * (map_line_cnt + 1));
	pre->data->map[map_line_cnt] = NULL;
	close(fd);
}

void	get_map(t_pre_data *pre, t_data *data, char *line, int offset)
{
	if (line[0] == '\n' && data->y_max == 0)
		return ;
	if (data->y_max == 0)
		make_map_space(pre, offset);
	data->map[data->y_max++] = my_strdup(line);
	if (data->x_max < my_strlen(line))
		data->x_max = my_strlen(line);
}

void	check_last_line_ln(char ***info_map)
{
	int		i;
	char	**map;
	char	*temp;
	int		len;

	map = *info_map;
	i = 0;
	while (map[i])
	{
		len = (my_strlen(map[i]));
		i++;
		if (map[i] == NULL && map[i - 1][len] == '\0')
		{
			temp = malloc(sizeof(char) * len + 2);
			if (temp == NULL)
				exit_error(MALLOC_FAILED, NULL);
			my_strcpy(temp, map[i - 1]);
			temp[len] = '\n';
			temp[len + 1] = '\0';
			single_free(&map[i - 1]);
			map[i - 1] = temp;
			break ;
		}
	}
}

void	parse_cub_file(t_pre_data *pre)
{
	int		cnt;
	int		offset;
	char	*line;
	int		fd;

	fd = open(pre->cub_file_name, O_RDONLY);
	if (fd == -1)
		exit_error(OPEN_ERROR, pre->cub_file_name);
	cnt = 0;
	offset = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (cnt == 6)
			get_map(pre, pre->data, line, offset);
		else if (get_map_info(pre, line) != -1)
			cnt++;
		single_free(&line);
		offset++;
	}
	close(fd);
	if (pre->data->map == NULL)
		exit_error(EMPTY_MAP, NULL);
}
