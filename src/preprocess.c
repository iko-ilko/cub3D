#include "../include/cub3d.h"
#include "../include/get_next_line.h"


void	init_pre_data(t_pre_data *data, t_map_info *map_info)
{
	data->y_max = 0;
	data->x_max = 0;
	// data->cub_file = NULL;
	data->north_arv = NULL;
	data->south_arv = NULL;
	data->west_arv = NULL;
	data->east_arv = NULL;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->cub_file_fd = -1;
	data->map = NULL;
	data->map_info = map_info;
	map_info->north = NULL;///////////사실상 값 바로 넣으니 초기화 안해도됨
	map_info->south = NULL;
	map_info->west = NULL;
	map_info->east = NULL;
	map_info->floor_color = -1;
	map_info->ceiling_color = -1;//////////
}

// char	**get_map(t_pre_data *data, char *file)
// {
// 	int		fd;
// 	int		i;
// 	char	*temp;
// 	char	*one_line;

// 	fd = open(file, O_RDONLY);
// 	if (fd == -1)
// 		exit_error(OPEN_ERROR, file);
// 	i = 0;
// 	one_line = NULL;
// 	while (1)
// 	{
// 		temp = get_next_line(fd);
// 		if (temp == NULL)
// 			break ; 
// 		one_line = ft_strjoin(one_line, temp);
// 		single_free(&temp);
// 		data->y_size++;
// 	}
// 	if (data->y_size == 0)//need to change (not so_long ..)
// 		exit_error(EMPTY_FILE, file);
// 	close(fd);
// 	return (ft_split(one_line, ' '));
// }

//갖고 온 line을 split('white space') 하고 map_info의 멤버 변수들에 값을 넣어주고(중복 체크는 초기화한 값이 아니면 중복에러)
//각 맞는 변수에 이미지 포인터 or RGB값 넣어주기
//각각의 요소는 개행 or 빈 줄 로 구분(한 라인씩 받아오며 비어있지 않다면 저 여섯개 체크. 각 요소에 해당되면 cnt == 6이면 그 아래는 맵으로(라인 다 쳐내고) 인식.)
//그 각 요소를 넣을라는데 NULL이 아니면 중복된 요소가 있다고 판단하고 에러처리.
int	get_map_info(t_pre_data *data, char *line)
{
	char	**arv;

	if (line[0] == '\0')
		return (-1);
	arv = ft_split(line, " ");
	if (arv[0] == NULL || arv[1] == NULL || arv[2] != NULL)//arv[0]은 공백으로만 이루어진 line인 경우.
		exit_error(MAP_INFO_LINE_ERROR, line);
	if (ft_strcmp("NO", arv[0]) == 0 && data->north_arv == NULL)
		data->north_arv = arv;
	else if (ft_strcmp("SO", arv[0]) == 0 && data->south_arv == NULL)
		data->south_arv = arv;
	else if (ft_strcmp("WE", arv[0]) == 0 && data->west_arv == NULL)
		data->west_arv = arv;
	else if (ft_strcmp("EA", arv[0]) == 0 && data->east_arv == NULL)
		data->east_arv = arv;
	else
		exit_error(MAP_INFO_LINE_ERROR, line);
	return (0);
}

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
	data->cub_file_fd = open(arv[1], O_RDONLY);
	if (data->cub_file_fd == -1)
		exit_error(OPEN_ERROR, arv[1]);
	// data->cub_file = parse_file_to_strings(arv[1]);
}

void	get_map(t_pre_data *data, t_map_info *map_info, char *line)
{
	//시작 빈 줄 먼저 쳐내고 empty line error
	//다시 반복문으로 line 받아와서 맵을 map_info->map 에 원본 받아오고 data의 y_max, x_max값도 넣고
	//data->map은 위의 내용 토대로 사방에 빈공간 추가하고 맵 체크하기.
	여기하기
}
void	parse_cub_file(t_pre_data *data)
{
	int		cnt;
	char	*line;

	cnt = 0;
	while (1)
	{
		
		line = get_next_line(data->cub_file_fd);
		if (line == NULL)
			break ;
		if (cnt == 6)
		{
			get_map(data, data->map_info, line);//break ? 
			break ;
		}
		else if (get_map_info(data, line) != -1)
			cnt++;
		single_free(&line);
	}
	close(data->cub_file_fd);
	// return (ft_split(one_line, ""));
}

void	preprocess(t_pre_data *data, t_map_info *map_info, int arc, char **arv)
{
	init_pre_data(data, map_info);
	check_arv(&data, arc, arv);//need to check
	parse_cub_file(data);

	// load_xmp_texture();
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