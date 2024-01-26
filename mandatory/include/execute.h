/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:32:05 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/26 04:48:41 by ilko             ###   ########.fr       */
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
# include "../mlx/mlx.h"
# include "type.h"

# define TRUE 1
# define FALSE 0
# define PLUS 1
# define MINUS 2
# define CROSS 3
# define MULTI 4
# define SUCCESS 0
# define FOV 66
# define WIN_HOR 500
# define WIN_VER 500
# define IMG_HOR 64 /* 이미지 사이즈 일단 이렇게 해서 진행. */
# define IMG_VER 64 /* 이미지 사이즈 일단 이렇게 해서 진행. */
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define EXIT_BUTTON_PRESS 17
# define ESC 65307
# define UP 65362
# define W 119
# define RIGHT 65363
# define D 100
# define DOWN 65364
# define S 115
# define LEFT 65361
# define A 97

/* utils.c */
void		my_mlx_pixel_put(t_image *img, int x, int y, int color);
int			ft_key_action(int key, t_data *img);

/* utils2.c */
double		ft_abs(double i);
double		deg_to_rad(double deg);

/* key_actionn.c */
void		player_move(t_data *data, int key);

/* vector.c */
t_vector	vector_calculate(t_vector v1, t_vector v2, int sign);
t_vector	vector_normalizing(t_vector vector);
double		vector_gradient(t_vector vector);
t_vector	vector_rotate(t_vector vec, double angle);
double		vector_gradient(t_vector vector);
t_vector	vector_multiple(t_vector vector, double scale);

/* ray_casting.c */
void		set_dda(t_data *data, t_ray *ray);
void		perform_dda(t_data *data, t_ray *ray);
void		init_ray(t_data *data, t_ray *ray, int x);
void		calculate_line_height(t_ray *ray, t_point *point);
void		plot_line(t_data *data, int x, t_ray *ray);

int			ray_casting(t_data *data);
int			get_color(t_image *texture, int pixel_x, int pixel_y);

/* get_texture_color.c */
int			get_texture_index(t_ray *ray);
void		find_texture_x(t_ray *ray);
void		put_texture_color(t_data *data, t_ray *ray, int x, int y);

#endif
