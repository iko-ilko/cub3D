/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:32:05 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/08 22:17:12 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <mlx.h> /* 지금 내장 mlx 로 진행하고 있으므로 필요할 시 변경해야함. */
# define TRUE 1
# define FALSE 0
# define PLUS 1
# define MINUS 2
# define CROSS 3
# define SUCCESS 0
# define FOV 66
# define WIN_HOR 500
# define WIN_VER 500

typedef int bool;

/* ray 벡터 구조체는 함수 내에서 이걸로 만들어서 쓰고 버리면 될듯. */
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

/* 이미지의 주소와 가로 세로 길이값이 중요하다.*/
typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
}	t_image;

/* 지금 더 필요한 것. 플레인 벡터 구조체, 시야 벡터 구조체 */
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}	t_data;

/* utils.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		mlx_image_find_color(t_image *img, int x, int y);
int		ft_key_action(int key, t_data *img);

/* vector.c */
t_vector    vector_calculate(t_vector v1, t_vector v2, int sign);
t_vector    vector_normalizing(t_vector vector);
double  	vector_gradient(t_vector vector);
#endif
