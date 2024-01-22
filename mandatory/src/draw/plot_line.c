#include "../../include/cub3d.h"

void    plot_line(t_data *data, int x, t_dda *dda)
{
    int y;

    y = 0;
    while (y < (WIN_VER  - dda->height) / 2)
    {
        my_mlx_pixel_put(&data->palette, x, y, 0x00ff00/*천장 색깔*/);
        y++;
    }
    while (y >= (WIN_VER  - dda->height) / 2 && y < (WIN_VER + dda->height) / 2)
    {
        my_mlx_pixel_put(&data->palette, x, y, 0xff00ff/*pick_wall_color*/);
        y++;
    }
    while (y <= WIN_VER)
    {
        my_mlx_pixel_put(&data->palette, x, y, 0x0000ff/*바닥 색깔*/);
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->palette.img, 0, 0);
}
