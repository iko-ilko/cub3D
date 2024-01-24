/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:39:21 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/24 14:11:28 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * img의 특정 좌표에 점을 찍기 위해 만드는 커스텀 함수.  
*/
void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_HOR - 1 || y >= WIN_VER - 1)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_texture_x(t_dda *dda, t_data *data)
{
	int	tex_x;
	double	wall_x;

	if (dda->side_wall == 0)
		wall_x = data->point.player.x + dda->wall_dist * dda->ray.x;
	else
		wall_x = data->point.player.y + dda->wall_dist * dda->ray.y;
	printf("wall_x %f\n", wall_x);
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * IMG_HOR);
	if (dda->side_wall == 0 && dda->ray.x > 0)
		tex_x = IMG_HOR - tex_x - 1;
	if (dda->side_wall == 1 && dda->ray.y < 0)
		tex_x = IMG_HOR - tex_x - 1;
	return (tex_x);
}

int	get_texture_y(t_dda *dda, int y)
{
	int	start;
	
	start = (WIN_VER - dda->height) / 2;
	return (IMG_VER - (y - start) * IMG_VER / WIN_VER);
}

/* 이미지 포인터와 좌표값을 넣었을 때 해당 좌표가 가진 칼라 값을 unsigned int 로 반환 */
int	get_color(t_image *texture, int pixel_x, int pixel_y)
{
	return (*(unsigned int *)((texture->addr + (pixel_y * texture->line_length)
			+ (pixel_x * texture->bits_per_pixel / 8))));
}

double	ft_abs(double i)
{
	return ((i * (i >= 0) + -i * (i < 0)));
}
