#include "../include/cub3d.h"

// void	remake_map(t_pre_data *data, t_map_info *map_info,char **map)
// {
	// remake_map(data, data->map_info, map);
	// 맵 복사하면서 (data->map_to_check로)
	// 맵 문자 하나하나 체크하고 값 바꾸고(ㄱㅗㅇ배ㄱ 으로)) 있있으면 안되는 문자도 체크.
// 	int	i;
// 	int	j;
// printf("-----\n");
// 	data->remap = malloc(sizeof(char *) * (map_info->y_max + 2));
// 	i = 0;
// 	while (i < map_info->y_max)
// 	{
// 		data->remap[i] = malloc(sizeof(char) * (map_info->x_max + 2));
// 		j = 0;
// 			// printf("!%s\n", map[i]);
// 		while (j < map_info->x_max)
// 		{
// 			if (i == 0 || j == 0 || i == map_info->y_max - 1 || j == map_info->x_max - 1)
// 				data->remap[i][j] = ' ';
// 			else if (j > ft_strlen(map[i - 1]))
// 				data->remap[i][j] = ' ';
// 			else if (map[i - 1][j - 1] == '\n')
// 				data->remap[i][j] = ' ';
// 			else
// 				data->remap[i][j] = map[i - 1][j - 1];
// 			printf("%c", data->remap[i][j]);
// 			j++;
// 		}
// 		printf("\n");
// 		i++;
// 	}//마지막 라인 개행 없으면 공백으로 처리돼서 나중에 세그폴트 날 수 있으니 체크 필요.
// 	for (int k = 0; k < map_info->y_max; k++)
// 		printf("%s\n", data->remap[k]);
// printf("-----\n");
// }
void	check_vaild_letter(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' \
		|| c == ' ' || c == '\n')
		return ;
	else
		exit_error(INVAILD_LETTER, &c);
}

// void	check_route(char **map, int idx[2], int len, int flag)
// {
// 	if (idx[Y] == 0 || idx[X] == 0 || map[idx[Y]]  || idx[X] == len)
// }
// void	check_vaild_route(char **map, int idx[2])
// {
// 	int	len;

// 	len = ft_strlen(map[idx[Y]]);
// 	check_route(map, idx, len, SANG);//x_max는 len, y_max는 다음 포인터가 널 포인터면
// 	len = ft_strlen(map[idx[Y]]);
// 	check_route(map, idx, len, HA);
// 	len = ft_strlen(map[idx[Y]]);
// 	check_route(map, idx, len, JOA);
// 	len = ft_strlen(map[idx[Y]]);
// 	check_route(map, idx, len, WOO);
// }

void	check_map(char **map, int y_max, int x_max)
{
	int	idx[2];
	// int	max[2];

	// max[Y] = y_max;
	// max[X] = x_max;
	idx[Y] = 0;
	while (idx[Y] < y_max)
	{
		idx[X] = 0;
		while (idx[X] < x_max)
		{
			if (map[idx[Y]][idx[X]] == '\0')
				break ;
			check_vaild_letter(map[idx[Y]][idx[X]]);
			if (map[idx[Y]][idx[X]] == '0')
				// check_vaild_route(map, idx);
			idx[X]++;
		}
		idx[Y]++;
	}

	
}
