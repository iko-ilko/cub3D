#include "../../include/cub3d.h"

void    plot_line(t_data *data, int x, int height)
{
    int y;

    y = 0;
    while (y < 2 / height)
    {
        my_mlx_pixel_put(data, x, y, /*천장 색깔*/);
        y++;
    }
    while (y >= 2 / height && y < IMG_VER - 2 / height)
    {
        my_mlx_pixel_put(data, x, y, /*pick_wall_color*/);
        y++;
    }
    while (y <= IMG_VER)
    {
        my_mlx_pixel_put(data, x, y, /*바닥 색깔*/);
        y++;
    }
}