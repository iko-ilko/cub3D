#include "cub3d.h"

<<<<<<< HEAD
void	map_info_print(t_map_info *map_info)
{
	char	**map = map_info->map;

	printf("----------------------------------------\n");
	printf("north texture pointer: %p\n", map_info->image[NORTH].img);
	printf("south texture pointer: %p\n", map_info->image[SOUTH].img);
	printf("west texture pointer: %p\n", map_info->image[WEST].img);
	printf("east texture pointer: %p\n", map_info->image[EAST].img);
	printf("ceiling RED: %d GREEN: %d BLUE: %d\n", map_info->ceiling_color / 256 / 256 % 256, map_info->ceiling_color / 256 % 256, map_info->ceiling_color % 256);
	printf("floor RED: %d GREEN: %d BLUE: %d\n", map_info->floor_color / 256 / 256 % 256, map_info->floor_color / 256 % 256, map_info->floor_color % 256);
	int i;
	for (i = 0; map != NULL && map[i] != NULL; i++)
		printf("%s", map[i]);
	printf("y size: %d x size:%d\n", map_info->y_max, map_info->x_max);
=======
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
>>>>>>> 7c344c0af16dcd2c71e7b2e1eb2dc622e8f710df
	printf("----------------------------------------\n");
	
}
