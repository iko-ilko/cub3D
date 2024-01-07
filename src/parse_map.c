#include "../include/cub3d.h"
#include "../include/get_next_line.h"
//빈 줄이 아니면 서브젝트에 따라 엄격한 규칙을 따름. 각 요소의 유형은 공백으로 구분 가능.
int	get_map_info(t_pre_data *data, char *line)
{
	char	**arv;

	if (line[0] == '\n')
		return (-1);
	arv = my_split(line, " ");
	if (arv[0] == NULL || arv[1] == NULL || arv[2] != NULL)//arv[0]은 공백으로만 이루어진 line인 경우.
		exit_error(MAP_INFO_LINE_ERROR, line);
	if (my_strcmp("NO", arv[0]) == 0 && data->north_arv == NULL)
		data->north_arv = arv;
	else if (my_strcmp("SO", arv[0]) == 0 && data->south_arv == NULL)
		data->south_arv = arv;
	else if (my_strcmp("WE", arv[0]) == 0 && data->west_arv == NULL)
		data->west_arv = arv;
	else if (my_strcmp("EA", arv[0]) == 0 && data->east_arv == NULL)
		data->east_arv = arv;
	else if (my_strcmp("F", arv[0]) == 0 && data->floor_arv == NULL)
		data->floor_arv = arv;
	else if (my_strcmp("C", arv[0]) == 0 && data->ceiling_arv == NULL)
		data->ceiling_arv = arv;
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

	if (line[0] == '\n' && map_info->y_max == 0)
		return ;
	if (map_info->y_max == 0)
		make_map_space(data, offset);
	map_info->map[map_info->y_max++] = my_strdup(line);
	if (map_info->x_max < my_strlen(line))
		map_info->x_max = my_strlen(line);
}

void	check_last_line_ln(char ***info_map, int y_max)
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
			single_free(&map[i]);
			map[i - 1] = temp;
			break ;
		}
	}
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
	if (data->map_info->map == NULL)
		exit_error(EMPTY_MAP, NULL);
}
