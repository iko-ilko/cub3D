/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:39:21 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/26 04:35:11 by ilko             ###   ########.fr       */
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
	*(unsigned int *)dst = color;
}

/* 이미지 포인터와 좌표값을 넣었을 때 해당 좌표가 가진 칼라 값을 unsigned int 로 반환 */
int	get_color(t_image *texture, int pixel_x, int pixel_y)
{
	return (*(unsigned int *)((texture->addr + (pixel_y * texture->line_length)
			+ (pixel_x * texture->bits_per_pixel / 8))));
}
