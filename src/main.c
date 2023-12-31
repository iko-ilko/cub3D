#include "../include/cub3d.h"


int main(int arc, char **arv)
{
	t_pre_data	data;
	int	fd;
	char	*temp;
	
	init_pre_data(&data);
	check_arv(&data, arc, arv);
	printf("%s\n", arv[1]);

}