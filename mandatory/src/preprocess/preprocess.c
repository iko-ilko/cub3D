#include "../include/cub3d.h"
#include "../include/get_next_line.h"


void	init_pre_struct(t_pre_data *pre, t_data *data, char **arv)
{
	pre->cub_file_name = NULL;
	pre->north_arv = NULL;
	pre->south_arv = NULL;
	pre->west_arv = NULL;
	pre->east_arv = NULL;
	pre->floor_arv = NULL;
	pre->ceiling_arv = NULL;
	pre->remap = NULL;
	pre->data = data;
	data->map = NULL;
	data->y_max = 0;
	data->x_max = 0;
}

void	check_arv(t_pre_data *pre, int arc, char **arv)
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
	pre->cub_file_name = my_strdup(arv[1]);
}

void	clear_pre_data(t_pre_data *pre)
{
	single_free(&pre->cub_file_name);
	double_free(&pre->north_arv);
	double_free(&pre->south_arv);
	double_free(&pre->west_arv);
	double_free(&pre->east_arv);
	double_free(&pre->floor_arv);
	double_free(&pre->ceiling_arv);
	double_free(&pre->remap);
}

void	preprocess(t_data *data, int arc, char **arv)
{
	t_pre_data	pre;

	init_pre_struct(&pre, data, arv);
	check_arv(&pre, arc, arv);
	parse_cub_file(&pre);
	check_last_line_ln(&data->map, data->y_max);
	load_xpm_texture(&pre, data, data->image);
	convert_rgb(&pre, data);
	remake_map(&pre, data, data->map);
	check_map(pre.remap, data->y_max, data->x_max);
	clear_pre_data(&pre);
}
