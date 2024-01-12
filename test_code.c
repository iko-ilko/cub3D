#include "cub3d.h"

void	map_info_print(t_data *data)
{
	char	**map = data->map;

	printf("----------------------------------------\n");
	printf("north texture pointer: %p\n", data->image[NORTH].img);
	printf("south texture pointer: %p\n", data->image[SOUTH].img);
	printf("west texture pointer: %p\n", data->image[WEST].img);
	printf("east texture pointer: %p\n", data->image[EAST].img);
	printf("ceiling RED: %d GREEN: %d BLUE: %d\n", data->ceiling_color / 256 / 256 % 256, data->ceiling_color / 256 % 256, data->ceiling_color % 256);
	printf("floor RED: %d GREEN: %d BLUE: %d\n", data->floor_color / 256 / 256 % 256, data->floor_color / 256 % 256, data->floor_color % 256);
	int i;
	for (i = 0; map != NULL && map[i] != NULL; i++)
		printf("%s", map[i]);
	printf("y size: %d x size:%d\n", data->y_max, data->x_max);
	printf("----------------------------------------\n");
	
}
