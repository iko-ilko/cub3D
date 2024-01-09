#include "../include/cub3d.h"


int main(int arc, char **arv)
{
	t_pre_data	data;
	t_map_info	map_info;

	int		fd;
	char	*temp;
//파싱에서 쓰이는 데이터 구조체 따로 분리하지않고 실행에 넘겨줄 때 포인터나 값 복사 해주는 쪽으로 하자.
	preprocess(&data, &map_info, arc, arv);
	mlx_put_image_to_window(map_info.mlx, map_info.win, map_info.image[NORTH].img, 0, 0);
	mlx_put_image_to_window(map_info.mlx, map_info.win, map_info.image[SOUTH].img, 100, 0);
	mlx_put_image_to_window(map_info.mlx, map_info.win, map_info.image[WEST].img, 200, 0);
	mlx_put_image_to_window(map_info.mlx, map_info.win, map_info.image[EAST].img, 300, 0);
	printf("%d %d %d %d\n", map_info.image[NORTH].width, map_info.image[SOUTH].width, map_info.image[WEST].width, map_info.image[EAST].width);

	mlx_loop(map_info.mlx);
}