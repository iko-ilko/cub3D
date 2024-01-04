#include "../include/cub3d.h"
#include "../include/get_next_line.h"


void	init_pre_struct(t_pre_data *data, t_map_info *map_info, char **arv)
{
	data->cub_file_name = NULL;
	data->north_arv = NULL;
	data->south_arv = NULL;
	data->west_arv = NULL;
	data->east_arv = NULL;
	data->floor_color_arv = NULL;
	data->ceiling_color_arv = NULL;
	data->map_to_check = NULL;
	data->map_info = map_info;
	map_info->y_max = 0;
	map_info->x_max = 0;
	map_info->north = NULL;///////////사실상 값 바로 넣으니 초기화 안해도됨
	map_info->south = NULL;
	map_info->west = NULL;
	map_info->east = NULL;
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
		exit_error(MANY_ARG, NULL);
	if (arc > 2)
		exit_error(FEW_ARG, NULL);
	i = 1;
	if (ft_strlen(arv[1]) < 5)
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
	// data->cub_file = parse_file_to_strings(arv[1]);
}
void	window_init(t_map_info *map_info)
{
	map_info->mlx = mlx_init();
	map_info->win = mlx_new_window(map_info->mlx, 500, 1000, "cub3D_test");
}

void	preprocess(t_pre_data *data, t_map_info *map_info, int arc, char **arv)
{
	init_pre_struct(data, map_info, arv);
	window_init(map_info);
	check_arv(data, arc, arv);//need to check
	parse_cub_file(data);
	// load_xmp_texture(data, map_info);
									map_info_print(map_info);//delete


	// convert_rgb();
	// check_map();//여기서 map_info->map = data->map;
	// free_pre_data();//map_info 와 map은 free XXXXX

	// check_map_info(data);//check "NO" "SO" . . . . || "F" "C"
	// check_map_data();//ㄱㅗㅇ배ㄱ split하고 체크해봐도 될듯? 섬맵 살릴 수 ..아니다 그럼 벽 검사가 불가능해진다.. 각각 체크 해 봐야 할듯
			//check_map_data()ㄴㅡㄴ ㄷㅗㅇ영형님의 말씀대로 맵 데이터 구역을 벽으로 감싼다음 dfs로 player를 만나는지 체크하면 벽에 구멍났는지 체크 가능, player위치에서 dfs다시 돌리며 다른 문자 체크.
			//ㄴ-> 사방에 라인 추가하고 0으로 채우고 dfs-> 플레이어 만나면(4개의 문자) 벽이 감싸져있는게 아니므로 에러.
	// data->map = get_map(data, arv[1]);//need to change (not so_long ..)
	// for (int i = 0; data->map[i]; i++)
	// 	printf("%s", data->map[i]);
}