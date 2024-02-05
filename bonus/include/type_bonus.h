/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongwol <seongwol@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:29:56 by seongwol          #+#    #+#             */
/*   Updated: 2024/02/05 15:29:59 by seongwol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*addr;
}	t_image;

/* ray 벡터 구조체는 함수 내에서 이걸로 만들어서 쓰고 버리면 될듯. */
typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_point
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	int			is_move;
	int			is_rotate;
	t_vector	move;
}	t_point;

typedef struct s_data
{
	int					y_max;
	int					x_max;
	char				**map;
	int					endian;
	void				*mlx;
	void				*mlx_win;
	unsigned int		floor_color;
	unsigned int		ceiling_color;
	t_image				image[4];
	t_image				minimap;
	t_image				palet;
	t_point				point;
}	t_data;

typedef struct s_pre_data
{
	char				*cub_file_name;
	char				**north_arv;
	char				**south_arv;
	char				**west_arv;
	char				**east_arv;
	char				**floor_arv;
	char				**ceiling_arv;
	char				**remap;
	struct s_data		*data;
}	t_pre_data;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		position;
	int		tex_x;
	int		tex_y;
	int		color;
}	t_ray;
#endif
