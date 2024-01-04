#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define MANY_ARG "too many argument"
# define FEW_ARG "too few argument"
# define OPEN_ERROR "open error"
# define EMPTY_FILE "empty file"
# define MALLOC_FAILED "malloc_failed"
# define FILE_NAME_ERROR "file name error"
# define MAP_INFO_LINE_ERROR "map_info_error"
// # define DUPLICATE_ELEMANT "duplicate elements"

# define MAP_SIZE_ERROR 3
# define MAP_ERROR 5
# define MLX_ERROR 6

typedef struct s_pre_data
{
	char				*cub_file_name;
	char				**north_arv;//char ** 로 담았다가 아래서 주자
	char				**south_arv;
	char				**west_arv;
	char				**east_arv;
	char				**floor_color_arv;//int ? uns int?
	char				**ceiling_color_arv;//놈이 문제라면 이름 줄이기
	// int					cub_file_fd;
	char				**map_to_check;
	struct s_map_info	*map_info;
}	t_pre_data;

typedef struct s_map_info
{
	int					y_max;
	int					x_max;
	char	**map;//메모리 최적화가 필요하다면 빈 줄, 공백 없앤 맵을 보내줄 수 있음.
	void	*north;
	void	*south;
	void	*west;
	void	*east;
	int		floor_color;
	int		ceiling_color;
}	t_map_info;

/* test_code.c *///delete
void	map_info_print(t_map_info *map_info);

/* preprocess.c */
void	preprocess(t_pre_data *data, t_map_info *map_info, int arc, char **arv);
void	init_pre_data(t_pre_data *data, t_map_info *map_info, char **arv);
void	parse_cub_file(t_pre_data *data);//process_map_file.c
int		get_map_info(t_pre_data *data, char *line);//process_map_file.c
void	make_map_space(t_pre_data *data, int offset);//process_map_file.c
void	get_map(t_pre_data *data, t_map_info *map_info, char *line, int offset);//process_map_file.c
void	check_arv(t_pre_data *data, int arc, char **arv);
// void	check_map_info(t_pre_data *data);
// char	**parse_file_to_strings(char *file);
// char	**get_map(t_pre_data *data, char *file);



/* util.c */
void	exit_error(char *str, char *reason);
void	single_free(char **p);
void	free_double(char ***p);



/* str_func.c */
int		ft_strlen(char *s);//my_ 이름 바꾸기
char	*ft_strjoin(char *s1, char *s2);//my_ 이름 바꾸기
int		my_strlcpy(char *dst, char *src, int dstsize);
int		ft_strcmp(char *s1, char *s2);//my_ 이름 바꾸기
char	*my_strdup(char *s1);


/* split.c */
char	**ft_split(char *s, char *sepa);



#endif