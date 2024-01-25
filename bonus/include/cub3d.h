/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilko <ilko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 19:21:28 by ilko              #+#    #+#             */
/*   Updated: 2024/01/26 02:31:50 by ilko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include "mlx.h"
# include "execute.h"
# include "../libft/libft.h"
# include "type.h"

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

# define Y 0
# define X 1

# define NORTH 0 //UP
# define SOUTH 1 //DOWN
# define WEST 2 //LEFT
# define EAST 3 //RIGHT

# define BLOCK_MAX 11//
# define MULTIPLE 8//

/* preprocess.c */
void	preprocess(t_data *data, int arc, char **arv);
void	init_pre_struct(t_pre_data *pre, t_data *data);
void	check_arv(t_pre_data *pre, int arc, char **arv);
void	clear_pre_data(t_pre_data *pre);

/* parse_map.c */
void	check_last_line_ln(char ***info_map);
void	parse_cub_file(t_pre_data *pre);
int		get_map_info(t_pre_data *pre, char *line);
void	make_map_space(t_pre_data *pre, int offset);
void	get_map(t_pre_data *pre, t_data *data, char *line, int offset);

/* convert_map_data.c */
void	sanitize_filename(t_pre_data *pre);
void	load_xpm_texture(t_pre_data *pre, t_data *data, t_image img[4]);
int		convert_rgb_int(char **rgb_str, char *line);
void	convert_rgb(t_pre_data *pre, t_data *data);

/* check_map.c */
void	remake_map(t_pre_data *pre, t_data *data, char **map);
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