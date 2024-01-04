#include "../include/cub3d.h"

void	load_xpm_texture(t_pre_data *data, t_map_info *map_info)
{
	int	width;
	int	height;

	map_info->north = mlx_xpm_file_to_image(map_info->mlx, data->north_arv[1], &width, &height);
	if (map_info->north == NULL)
		perror("test");
		// exit_error(MLX_ERROR, "north texture");
	printf("%s\n", map_info->north);ㅇㅕ기 테테스스트트
	exit((1));
}