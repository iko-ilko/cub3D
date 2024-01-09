#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "mlx.h"


# define MANY_ARG "too many argument"
# define FEW_ARG "too few argument"
# define OPEN_ERROR "open error"
# define EMPTY_MAP "empty map"
# define MALLOC_FAILED "malloc_failed"
# define FILE_NAME_ERROR "file name error"
# define MAP_INFO_LINE_ERROR "map info error"
# define RGB_VALUE_ERROR "invaild rgb value"
# define RGB_COUNT_ERROR "invaild rgb count"
# define INVAILD_LETTER "invalid map letter"
# define BREACHED_MAP "breached map"
# define MANY_PLAYER_LETTER "many player letter"

# define MAP_SIZE_ERROR 3
# define MAP_ERROR 5
# define MLX_ERROR 6

# define Y 0
# define X 1

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
	struct s_map_info	*map_info;
}	t_pre_data;

typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
}	t_image;

typedef struct s_map_info
{
	int					y_max;
	int					x_max;
	char				**map;
	void				*mlx;
	void				*win;
	int					floor_color;
	int					ceiling_color;
	struct s_image		image[4];
}	t_map_info;



/* preprocess.c */
void	preprocess(t_pre_data *data, t_map_info *map_info, int arc, char **arv);
void	init_pre_struct(t_pre_data *data, t_map_info *map_info, char **arv);
void	check_arv(t_pre_data *data, int arc, char **arv);
void	window_init(t_map_info *map_info);
void	clear_pre_data(t_pre_data *data);


/* parse_map.c */
void	check_last_line_ln(char ***info_map, int y_max);
void	parse_cub_file(t_pre_data *data);
int		get_map_info(t_pre_data *data, char *line);
void	make_map_space(t_pre_data *data, int offset);
void	get_map(t_pre_data *data, t_map_info *map_info, char *line, int offset);

/* convert_map_data.c */
void	sanitize_filename(t_pre_data *data);
void	load_xpm_texture(t_pre_data *data, t_map_info *info, t_image img[4]);
int		convert_rgb_int(char **rgb_str, char *line);
void	convert_rgb(t_pre_data *data, t_map_info *map_info);

/* check_map.c */
void	remake_map(t_pre_data *data, t_map_info *map_info, char **map);
void	check_route(char **map, int idx[2], int max[2], int flag);
void	check_vaild_route(char **map, int idx[2], int max[2]);
void	check_vaild_letter(char c, char *line, int *player_cnt);
void	check_map(char **map, int y_max, int x_max);



/* util.c */
void	exit_error(char *str, char *reason);
void	single_free(char **p);
void	double_free(char ***p);



/* str_func1.c */
int		my_strlen(char *s);
char	*my_strjoin(char *s1, char *s2);
int		my_strlcpy(char *dst, char *src, int dstsize);
int		my_strcmp(char *s1, char *s2);
char	*my_strdup(char *s1);

/* str_func2.c */
int		my_atoi_cub(char *str);
char	*my_strcpy(char *dest, char *src);


/* split.c */
char	**my_split(char *s, char *sepa);



#endif