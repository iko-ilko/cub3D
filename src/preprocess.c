#include "../include/cub3d.h"
#include "../include/get_next_line.h"


void	init_pre_struct(t_pre_data *data, t_map_info *map_info, char **arv)
{
	data->cub_file_name = NULL;
	data->north_arv = NULL;
	data->south_arv = NULL;
	data->west_arv = NULL;
	data->east_arv = NULL;
	data->floor_arv = NULL;
	data->ceiling_arv = NULL;
	data->remap = NULL;
	data->map_info = map_info;
	map_info->map = NULL;
	map_info->y_max = 0;
	map_info->x_max = 0;
	map_info->floor_color = -1;
	map_info->ceiling_color = -1;//////////
}
//갖고 온 line을 split('white space') 하고 map_info의 멤버 변수들에 값을 넣어주고(중복 체크는 초기화한 값이 아니면 중복에러)
//각 맞는 변수에 이미지 포인터 or RGB값 넣어주기
//각각의 요소는 개행 or 빈 줄 로 구분(한 라인씩 받아오며 비어있지 않다면 저 여섯개 체크. 각 요소에 해당되면 cnt == 6이면 그 아래는 맵으로(라인 다 쳐내고) 인식.)
//그 각 요소를 넣을라는데 NULL이 아니면 중복된 요소가 있다고 판단하고 에러처리.


void	check_arv(t_pre_data *data, int arc, char **arv)
{
	int	i;
	int	idx;

	if (arc == 1)
		exit_error(FEW_ARG, NULL);
	if (arc > 2)
		exit_error(MANY_ARG, NULL);
	i = 1;
	if (my_strlen(arv[1]) < 5)
		exit_error(FILE_NAME_ERROR, arv[1]);
	while (i < arc)
	{
		idx = 0;
		while (arv[i][idx])
			idx++;
		if (idx <= 4 || arv[i][idx - 1] != 'b' || arv[i][idx - 2] != 'u'
		|| arv[i][idx - 3] != 'c' || arv[i][idx - 4] != '.')
			exit_error(FILE_NAME_ERROR, arv[1]);
		i++;
	}
	if (arv[1][idx - 5] == '/')
		exit_error(FILE_NAME_ERROR, arv[1]);
	data->cub_file_name = my_strdup(arv[1]);
}
void	window_init(t_map_info *map_info)
{
	map_info->mlx = mlx_init();
	map_info->win = mlx_new_window(map_info->mlx, 1000, 500, "cub3D_test");
}
void	clear_pre_data(t_pre_data *data)
{
	single_free(&data->cub_file_name);
	double_free(&data->north_arv);
	double_free(&data->south_arv);
	double_free(&data->west_arv);
	double_free(&data->east_arv);
	double_free(&data->floor_arv);
	double_free(&data->ceiling_arv);
	double_free(&data->remap);
}

void	preprocess(t_pre_data *data, t_map_info *map_info, int arc, char **arv)
{
	init_pre_struct(data, map_info, arv);
	window_init(map_info);
	check_arv(data, arc, arv);//need to check
	parse_cub_file(data);
	check_last_line_ln(&map_info->map, map_info->y_max);
	load_xpm_texture(data, map_info, &map_info->image);
	convert_rgb(data, map_info);
	remake_map(data, map_info, map_info->map);
	check_map(data->remap, map_info->y_max, map_info->x_max);
	clear_pre_data(data);

	map_info_print(map_info);//delete

}