#include "../include/cub3d.h"

t_vector    sight_rotate(t_vector change, int key)
{
    if (key == UP)
        return (change);
    else if (key == DOWN)
        return (vector_multiple(change, -1));
    else if (key == LEFT)
        return (vector_rotate(change, -M_PI_2));
    else
        return (vector_rotate(change, M_PI_2));\
}

void    player_move(t_data *data, int key)
{
    t_vector    change;
    change = vector_normalizing(data->point.sight);
    change = sight_rotate(change, key);
    change = vector_multiple(change, 0.1);
    data->point.player = vector_calculate(data->point.player, change, PLUS);
    data->point.plane = vector_calculate(data->point.plane, change, PLUS);
}