#include "../include/cub3d.h"


int main(int arc, char **arv)
{
	t_pre_data	data;
	t_map_info	map_info;

	int		fd;
	char	*temp;

	preprocess(&data, &map_info, arc, arv);
}