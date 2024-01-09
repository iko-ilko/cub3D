/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:49:20 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/08 22:17:15 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int main(int ac, char **av)
{
	t_data	img;
	t_vector player;

	 char	map[10][10] = {
	 	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	 	{1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 'N', 0, 1},
		{1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	(void)ac;	(void)av;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, WIN_HOR, WIN_VER, "cub3d");
	img.img = mlx_new_image(img.mlx, WIN_HOR, WIN_VER);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	/* 플레이어의 좌표를 받아오고, 바라보는 시야 벡터와 함께 리턴한다. */
	/* 시야 벡터를 바탕으로 플레인 벡터를 만들어서, 들고있는다. */
	/* while 문 */
	/* */
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_hook(img.mlx_win, 2, 0, ft_key_action, &img);
	mlx_loop(img.mlx);
}
