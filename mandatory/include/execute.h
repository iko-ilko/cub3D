/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:32:05 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/25 20:38:42 by ilko             ###   ########.fr       */
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
# define ESC 53
# define UP 126
# define W 13
# define RIGHT 124
# define D 2
# define DOWN 125
# define S 1
# define LEFT 123
# define A 0
# define SPACE 49

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

/* dda.c */
void		get_dist(t_point point, t_vector *dist, t_vector ray);
void		get_side(t_point point, t_vector *side, t_vector dist, t_vector ray);
void		set_step(t_vector sight, int *step_x, int *step_y);
int			ft_dda(t_data *data, t_vector *dist, t_vector *side, t_vector ray);
int			ray_casting(t_data *data);
int			get_color(t_image *texture, int pixel_x, int pixel_y);
#endif
