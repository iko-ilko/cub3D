/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:39:21 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/12 16:23:58 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/**
 * 해당 포인트가 벽인지 나타내는 함수. 브레젠험 알고리즘에서 이용할 예정.
*/
int	is_wall_hit(char **map, int x, int y)
{
	if (x / (10 * IMG_HOR) == 0)
		return (TRUE);
	else if (y / (10 * IMG_VER) == 0)
		return (TRUE);
	else
		return (FALSE);
}

/**
 * 광선이 동 서 남 북 중 어느 벽에 부딧혔는지 파악하는 함수.
 * 벡터는 plane - player 형식으로 계산되며, player에서 plane쪽으로 향하게 된다.
*/
int	wall_collision_direction(t_vector plane, t_vector player)
{
	double	dx;
	double	dy;
	double	magnitude;

	if(plane.x - player.x == 0)
		dx = 0.00000000001;
	else
		dx = plane.x - player.x;
	dy = plane.y = player.y;
	magnitude = dy / dx;
	if (magnitude >= 1)
		return (NORTH);
	else if (magnitude >= 0 && magnitude < 1)
		return (WEST);
	else if (magnitude < -1)
		return (SOUTH);
	else
		return (EAST);
}

/* img의 특정 좌표에 점을 찍기 위해 만드는 커스텀 함수. */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->x_max || y >= data->y_max)
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
