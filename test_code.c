#include "cub3d.h"

void	map_info_print(t_map_info *map_info)
{
	char	**map = map_info->map;

	printf("----------------------------------------\n");
	printf("ceiling RED: %d GREEN: %d BLUE: %d\n", map_info->ceiling_color / 256 / 256 % 256, map_info->ceiling_color / 256 % 256, map_info->ceiling_color % 256);
	printf("floor RED: %d GREEN: %d BLUE: %d\n", map_info->floor_color / 256 / 256 % 256, map_info->floor_color / 256 % 256, map_info->floor_color % 256);
	int i;
	for (i = 0; map != NULL && map[i] != NULL; i++)
		printf("%s", map[i]);
	printf("y size: %d x size:%d\n", map_info->y_max, map_info->x_max);
	printf("----------------------------------------\n");
	
}
