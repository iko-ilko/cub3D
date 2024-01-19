/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:32:05 by seongwol          #+#    #+#             */
/*   Updated: 2024/01/19 13:58:24 by seongwol         ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0
# define PLUS 1
# define MINUS 2
# define CROSS 3
# define MULTI 4//??
# define SUCCESS 0
# define FOV 66
# define WIN_HOR 500
# define WIN_VER 500
# define IMG_HOR 64 /* 이미지 사이즈 일단 이렇게 해서 진행. */
# define IMG_VER 64 /* 이미지 사이즈 일단 이렇게 해서 진행. */
# define KEY_PRESS 2//-----
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
# define SPACE 49//-----

typedef struct s_point		t_point;
typedef struct s_image		t_image;
typedef struct s_data		t_data;
typedef struct s_vector		t_vector;

/* utils.c */
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
int		mlx_image_find_color(t_image *img, int x, int y);
int		ft_key_action(int key, t_data *img);
double	ft_abs(double i);

/* vector.c */
t_vector    vector_calculate(t_vector v1, t_vector v2, int sign);
t_vector    vector_normalizing(t_vector vector);
double		vector_gradient(t_vector vector);
double		deg_to_rad(double deg);
t_vector	vector_rotate(t_vector vec, double angle);
double		vector_gradient(t_vector vector);
t_vector    vector_multiple(t_vector vector, double scale);

/* dda.c */
void	get_dist(t_point point, t_vector *dist, t_vector ray);
void	get_side(t_point point, t_vector *side, t_vector dist, t_vector ray);
void	set_step(t_vector sight, int *step_x, int *step_y);
int		ft_dda(t_data *data, t_vector *dist, t_vector *side, t_vector ray);
void	ray_casting(t_data *data);
double	get_wall_hight(t_data *data, t_point point, t_vector ray);

/* plot_line */
void    plot_line(t_data *data, int x, int height);


/* key_event */
int		press_key(int key, t_data *data);
int		release_key(int key, t_data *data);
int		check_wall(t_data *data, char **map, double p_x, double p_y);
void	check_move(t_data *data);
#endif
