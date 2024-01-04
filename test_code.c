#include "cub3d.h"

void	map_info_print(t_map_info *map_info)
{
	char	**map = map_info->map;

	printf("----------------------------------------\n");
	printf("north texture pointer: %p\n", map_info->north);
	printf("south texture pointer: %p\n", map_info->south);
	printf("west texture pointer: %p\n", map_info->west);
	printf("east texture pointer: %p\n", map_info->east);
	int i;
	for (i = 0; map != NULL && map[i] != NULL; i++)
		printf("%s", map[i]);
	printf("y size: %d x size:%d\n", map_info->y_max, map_info->x_max);
	printf("i:%d last:%s", i, map[i]);
	printf("----------------------------------------\n");
	
}
