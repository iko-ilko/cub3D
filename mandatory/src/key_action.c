#include "../include/cub3d.h"

t_vector    sight_rotate(t_vector change, int key)
{
    if (key == UP)
        return (change);
    else if (key == DOWN)
        return (vector_multiple(change, -1));
    else if (key == LEFT)
        return (vector_rotate(change, -M_PI_2));
    else if (key == RIGHT)
        return (vector_rotate(change, M_PI_2));
    else
        printf("error!!!!!!\n\n\n\n");
}

void    player_move(t_data *data, int key)
{
    t_vector    change;

    change = vector_normalizing(data->point.dir);
    change = sight_rotate(change, key);
    change = vector_multiple(change, 0.1);
    data->point.pos = vector_calculate(data->point.pos, change, PLUS);
}

/* 키를 입력할 때 발동하는 액션을 관리하는 함수 */
int	ft_key_action(int key, t_data *data)
{
	if (key == 53)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
	{
		player_move(data, key);
	}
    if (key == A || key == D)
    {
        data->point.dir = vector_rotate(data->point.dir, (-0.2 * (key == A) + 0.2 * (key == D)));
        data->point.plane = vector_rotate(data->point.plane, (-0.2 * (key == A) + 0.2 * (key == D)));
    }
	return (SUCCESS);
}
