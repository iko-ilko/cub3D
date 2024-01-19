
#ifndef MINIMAP_H
# define MINIMAP_H
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "execute.h"
# include "cub3d.h"
# include "type.h"
# include "../mlx/mlx.h"

# define MULTIPLE 16 //2의 제곱으로 나눠야 소수 오차 없을듯? //minimap 보정값
# define BLOCK_MAX 11 //미니맵에서 보여지는 블럭 개수 // 홀수면 치우쳐짐 // 가로세로 개수 다르게 하고싶으면 매크로 나누기
# define STEP 0.25 // 이정도 소수 오차는 허용 되는지 체크.

typedef struct s_point		t_point;
typedef struct s_image		t_image;
typedef struct s_data		t_data;
typedef struct s_vector		t_vector;

/* minimap.c */
void	start_minimap(t_data *data, double start[2], t_vector player_pos);
void	draw_player(t_data *data, char **map, t_image *minimap, double start[2]);
void	draw_minimap(t_data *data, char **map, t_image *minimap);
void	put_minimap(t_data *data, int minimap_x, int minimap_y);



#endif
