#include "../include/cub3d.h"
#include "../include/get_next_line.h"

int	get_map_info(t_pre_data *data, char *line)
{
	char	**arv;

	if (line[0] == '\n')
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
	else if (ft_strcmp("F", arv[0]) == 0 && data->floor_color_arv == NULL)
		data->floor_color_arv = arv;
	else if (ft_strcmp("C", arv[0]) == 0 && data->ceiling_color_arv == NULL)
		data->ceiling_color_arv = arv;
	else
		exit_error(MAP_INFO_LINE_ERROR, line);
	return (0);
}

void	make_map_space(t_pre_data *data, int offset)
{
	int		fd;
	int		map_line_cnt;
	char	*line;

	fd = open(data->cub_file_name, O_RDONLY);
	if (fd == -1)
		exit_error(OPEN_ERROR, data->cub_file_name);
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
	data->map_info->map = malloc(sizeof(char *) * (map_line_cnt + 1));
	data->map_info->map[map_line_cnt] = NULL;
	close(fd);
}

//ㅅㅓㅁ ㅁㅐㅂ ㄸㅒ무ㄴ에 빈 줄도 허용. 벽벽으으로  ㅈ둘러 쌓이지않은 문제가 있는 맵은 어차피 그 다음 맵 체크 단계에서 걸러진다.
void	get_map(t_pre_data *data, t_map_info *map_info, char *line, int offset)
{
	//시작 빈 줄 먼저 쳐내고 empty line error
	//다시 반복문으로 line 받아와서 맵을 map_info->map 에 원본 받아오고 data의 y_max, x_max값도 넣고
	//data->map은 위의 내용 토대로 사방에 빈공간 추가하고 맵 체크하기.
	if (line[0] == '\n' && map_info->y_max == 0)
		return ;
	if (map_info->y_max == 0)
		make_map_space(data, offset);
	map_info->map[map_info->y_max++] = my_strdup(line);
	if (map_info->x_max < ft_strlen(line))
		map_info->x_max = ft_strlen(line);
}

void	parse_cub_file(t_pre_data *data)
{
	int		cnt;
	int		offset;
	char	*line;
	int		fd;

	fd = open(data->cub_file_name, O_RDONLY);
	if (fd == -1)
		exit_error(OPEN_ERROR, data->cub_file_name);
	cnt = 0;
	offset = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (cnt == 6)
			get_map(data, data->map_info, line, offset);
		else if (get_map_info(data, line) != -1)
			cnt++;
		single_free(&line);
		offset++;
	}
	close(fd);
}