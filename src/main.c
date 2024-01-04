#include "../include/cub3d.h"


int main(int arc, char **arv)
{
	t_pre_data	data;
	t_map_info	map_info;

	int		fd;
	char	*temp;
//파싱에서 쓰이는 데이터 구조체 따로 분리하지않고 실행에 넘겨줄 때 포인터나 값 복사 해주는 쪽으로 하자.
	preprocess(&data, &map_info, arc, arv);
	printf("done\n");

}