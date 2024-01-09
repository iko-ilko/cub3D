/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:39:21 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/08 21:31:15 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/* img의 특정 좌표에 점을 찍기 위해 만드는 커스텀 함수. */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 /*|| x > max || y > max*/)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/* 이미지 포인터와 좌표값을 넣었을 때 해당 좌표가 가진 칼라 값을 unsigned int 로 반환 */
int	mlx_image_find_color(t_image *img, int x, int y) //ilko help!!!!!!!!!!
{
	unsigned int	*res;

	res = (unsigned int *)img->img + (y * img->width) + x;
	return (*res);
}

/* 키를 입력할 때 발동하는 액션을 관리하는 함수 */
int	ft_key_action(int key, t_data *img)
{
	if (key == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(0);
	}
	return (SUCCESS);
}
