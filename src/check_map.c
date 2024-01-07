#include "../include/cub3d.h"
//플레이어가 없는 구역에 벽으로 둘러쌓인 공백이 있다면 .. 벽으로 둘러쌓여는 있으니 괜찮다고 할 수는 있지만 그런 논리는 플레이어 구역에 공백이 있어도 된다는 말.

void	remake_map(t_pre_data *data, t_map_info *map_info, char **map)
{
	int	i;
	int	j;

	data->remap = malloc(sizeof(char *) * (map_info->y_max + 3));//y_max의 2줄 + 1(NULL)
	i = -1;
	while (++i < map_info->y_max + 2)
	{
		data->remap[i] = malloc(sizeof(char) * (map_info->x_max + 2));//개행이 항상 있으니 x는 + 2
		j = -1;
		while (++j < map_info->x_max + 1)
		{
			if (i == 0 || j == 0 || \
				i == map_info->y_max + 1 || j == map_info->x_max + 1)
				data->remap[i][j] = ' ';//나중에 공백으로 바꿔야함.///////////////
			else if (j > my_strlen(map[i - 1]))
				data->remap[i][j] = ' ';
			else if (map[i - 1][j - 1] == '\n' || map[i - 1][j - 1] == ' ')
				data->remap[i][j] = ' ';
			else
				data->remap[i][j] = map[i - 1][j - 1];
		}
		data->remap[i][j] = '\0';
	}
	data->remap[i] = NULL;
	map_info->x_max--;
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
	if (flag == SANG && idx[Y]--)
		check_route(map, idx, max, flag);
	else if (flag == HA && idx[Y]++)
		check_route(map, idx, max, flag);
	else if (flag == JOA && idx[X]--)
		check_route(map, idx, max, flag);
	else if (flag == WOO && idx[X]++)
		check_route(map, idx, max, flag);
}

void	check_vaild_route(char **map, int idx[2], int max[2])
{
	int	i[2];

	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, SANG);
	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, HA);
	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, JOA);
	i[Y] = idx[Y];
	i[X] = idx[X];
	check_route(map, i, max, WOO);
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
