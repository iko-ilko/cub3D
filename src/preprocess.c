#include "../include/cub3d.h"
#include "../include/get_next_line.h"


void	init_pre_data(t_pre_data *data)
{
	data->y_size = 0;
	data->map = NULL;
}

char	**get_map(t_pre_data *data, char *file)
{
	int		fd;
	int		i;
	char	*temp;
	char	*one_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error("open error: ", file);
	i = 0;
	one_line = NULL;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ; 
		one_line = ft_strjoin(one_line, temp);
		// one_free(&temp);//여기 함수 잘못됨.
		data->y_size++;
	}
	if (data->y_size == 0)
		exit_error("empty file: ", file);
	close(fd);
	return (ft_split(one_line, ' '));
}

void	check_arv(t_pre_data *data, int arc, char **arv)
{
	int	fd;

	if (arc == 1)
		exit_error("too few argument", NULL);
	if (arc > 2)
		exit_error("too many argument", NULL);
	data->map = get_map(data, arv[1]);
	for (int i = 0; data->map[i]; i++)
		printf("%s", data->map[i]);
		
}