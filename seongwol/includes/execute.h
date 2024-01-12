/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:32:05 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/12 17:59:54 by ilko             ###   ########.fr       */
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
# define IMG_HOR 64 /* 이미지 사이즈 일단 이렇게 해서 진행. */
# define IMG_VER 64 /* 이미지 사이즈 일단 이렇게 해서 진행. */
# define NORTH 0 //UP
# define SOUTH 1 //DOWN
# define WEST 2 //LEFT
# define EAST 3 //RIGHT

typedef struct s_pre_data
{
	char				*cub_file_name;
	char				**north_arv;
	char				**south_arv;
	char				**west_arv;
	char				**east_arv;
	char				**floor_arv;//int ? uns int?
	char				**ceiling_arv;//놈이 문제라면 이름 줄이기
	char				**remap;
	struct s_data	*map_info;
}	t_pre_data;

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
	int					y_max;
	int					x_max;
	char				**map;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	void				*mlx;
	void				*mlx_win;
	unsigned int		floor_color;
	unsigned int		ceiling_color;
	struct s_image		image[4];
}	t_data;

typedef struct s_point
{
	t_vector	player;
	t_vector	sight;
	t_vector	plane;
}	t_point;

/* utils.c */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		mlx_image_find_color(t_image *img, int x, int y);
int		ft_key_action(int key, t_data *img);

/* vector.c */
t_vector    vector_calculate(t_vector v1, t_vector v2, int sign);
t_vector    vector_normalizing(t_vector vector);
double  	vector_gradient(t_vector vector);
#endif
