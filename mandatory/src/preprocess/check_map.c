/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:25:49 by ilko              #+#    #+#             */
/*   Updated: 2024/01/24 11:25:57 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	remake_map(t_pre_data *pre, t_data *data, char **map)
{
	int	i;
	int	j;

	pre->remap = malloc(sizeof(char *) * (data->y_max + 3));
	i = -1;
	while (++i < data->y_max + 2)
	{
		pre->remap[i] = malloc(sizeof(char) * (data->x_max + 2));
		j = -1;
		while (++j < data->x_max + 1)
		{
			if (i == 0 || j == 0 || \
				i == data->y_max + 1 || j == data->x_max + 1)
				pre->remap[i][j] = ' ';
			else if (j > my_strlen(map[i - 1]))
				pre->remap[i][j] = ' ';
			else if (map[i - 1][j - 1] == '\n' || map[i - 1][j - 1] == ' ')
				pre->remap[i][j] = ' ';
			else
				pre->remap[i][j] = map[i - 1][j - 1];
		}
		pre->remap[i][j] = '\0';
	}
	pre->remap[i] = NULL;
	data->x_max--;
}

void	check_route(char **map, int idx[2], int max[2], int flag)
{
	if (idx[Y] == -1 || idx[X] == -1 || \
		idx[Y] == max[Y] + 2 || idx[X] == max[X] + 2)
		return ;
	if (map[idx[Y]][idx[X]] == '1')
		return ;
	if (map[idx[Y]][idx[X]] == ' ')
		exit_error(BREACHED_MAP, map[idx[Y]]);
	if (flag == NORTH && idx[Y]--)
		check_route(map, idx, max, flag);
	else if (flag == SOUTH && idx[Y]++)
		check_route(map, idx, max, flag);
	else if (flag == WEST && idx[X]--)
		check_route(map, idx, max, flag);
	else if (flag == EAST && idx[X]++)
		check_route(map, idx, max, flag);
}

void	check_vaild_route(char **map, int idx[2], int max[2])
{
	int	i[2];

	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, NORTH);
	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, SOUTH);
	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, WEST);
	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, EAST);
}

void	check_vaild_letter(char c, char *line, int *player_cnt)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (*player_cnt != 0)
			exit_error(MANY_PLAYER_LETTER, line);
		*player_cnt += 1;
		return ;
	}
	else if (c == '0' || c == '1')
		return ;
	else if (c == ' ' || c == '\n')
		return ;
	else
		exit_error(INVAILD_LETTER, line);
}

void	check_map(char **map, int y_max, int x_max)
{
	int	idx[2];
	int	max[2];
	int	player_cnt;

	player_cnt = 0;
	max[Y] = y_max + 1;
	max[X] = x_max + 1;
	idx[Y] = 1;
	while (idx[Y] < max[Y])
	{
		idx[X] = 1;
		while (idx[X] < max[X])
		{
			if (map[idx[Y]][idx[X]] == '\0')
				break ;
			check_vaild_letter(map[idx[Y]][idx[X]], map[idx[Y]], &player_cnt);
			if (map[idx[Y]][idx[X]] == '0')
				check_vaild_route(map, idx, max);
			idx[X]++;
		}
		idx[Y]++;
	}
}
