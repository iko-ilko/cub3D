#include "../include/cub3d.h"
#include "../include/get_next_line.h"


void	init_pre_data(t_pre_data *data)
{
	// data->y_size = 0;
	data->cub_file = NULL;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->map = NULL;
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
void	check_map_info(t_pre_data *data)
{

}
void	parse_file_to_strings(t_pre_data *data, char *file)
{
	data->cub_file 에 gnl로 가져온 file data 박기.
	그걸 토대로 map_info 체크, map_data체크 할거니까 ..
	깃 이그노어 추가하기
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
	parse_file_to_strings(data, arv[1]);
	// data->cub_file_fd = open(arv[1], O_RDONLY);
	// if (data->cub_file_fd == -1)
	// 	exit_error(OPEN_ERROR, arv[1]);
}

void	preprocess(t_pre_data *data, int arc, char **arv)
{
	init_pre_data(&data);
	check_arv(&data, arc, arv);//need to check
	check_map_info(data);//check "NO" "SO" . . . . || "F" "C"
	check_map_data();//ㄱㅗㅇ배ㄱ split하고 체크해봐도 될듯? 섬맵 살릴 수 ..아니다 그럼 벽 검사가 불가능해진다.. 각각 체크 해 봐야 할듯
	// data->map = get_map(data, arv[1]);//need to change (not so_long ..)
	// for (int i = 0; data->map[i]; i++)
	// 	printf("%s", data->map[i]);
}