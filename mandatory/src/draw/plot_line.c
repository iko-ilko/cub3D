#include "../../include/cub3d.h"

int set_type(t_dda *dda)
{
    double gradiant;

    gradiant = vector_gradient(dda->ray);
    if (gradiant < -1)
        return (NORTH);
    else if (gradiant >= -1 && gradiant < 0)
        return (EAST);
    else if (gradiant >= 1)
        return (SOUTH);
    else
        return (WEST);
}


void    plot_line(t_data *data, int x, t_dda *dda)
{
    t_texture t;
    int y;

    y = -1;
    while (++y < (WIN_VER - dda->height) / 2)
        my_mlx_pixel_put(&data->palette, x, y, 0x00ff00/*천장 색깔*/);
    while (++y >= (WIN_VER - dda->height) / 2 && y < (WIN_VER + dda->height) / 2)
    {
        t.tex_x = get_texture_x(dda, data);
        t.tex_y = get_texture_y(data, y);
        t.type = set_type(dda);
        t.color = get_color(&data->image[t.type], t.tex_x, t.tex_y);
        // printf("tex_x = %d, tex_y = %d, type = %d, color = %d\n", t.tex_x, t.tex_y, t.type, t.color);
        my_mlx_pixel_put(&data->palette, x, y, t.color);
    }
    while (++y <= WIN_VER)
        my_mlx_pixel_put(&data->palette, x, y, 0x0000ff/*바닥 색깔*/);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->palette.img, 0, 0);
}
