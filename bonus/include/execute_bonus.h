/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:29:50 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 19:34:38 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BONUS_H
# define EXECUTE_BONUS_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "type_bonus.h"

# define TRUE 1
# define FALSE 0
# define PLUS 1
# define MINUS 2
# define CROSS 3
# define SUCCESS 0
# define FOV 66
# define WIN_HOR 500
# define WIN_VER 500
# define IMG_HOR 64
# define IMG_VER 64
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
int			goodbye(t_data *data);
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

/* wall_check.c */
int			get_wall_index_x(int i, t_point point);
int			get_wall_index_y(int i, t_point point);
int			calculate_distance(t_vector pos, t_vector diff, int i);
double		set_corrected_pos(t_data *d, int move_i[4], int flag);

/* minimap.c */
void		put_minimap(t_data *data, int minimap_x, int minimap_y);

#endif
