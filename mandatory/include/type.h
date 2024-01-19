
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
	double	z;
}	t_vector;

typedef struct s_point
{
	t_vector	player;
	t_vector	sight;
	t_vector	plane;
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

	char	sight;
	t_image	palette;
	t_image	minimap;
	int		move_p[4];
	t_point	point;
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

#endif