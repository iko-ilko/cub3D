CC = cc  -g3 -Wall -Wextra -Werror
SRCS = ./src/main.c \
		./src/preprocess/preprocess.c \
		./src/preprocess/parse_map.c \
		./src/preprocess/convert_map_info.c \
		./src/preprocess/check_map.c \
		./src/preprocess/utils.c \
		./src/str_src/str_func1.c \
		./src/str_src/str_func2.c \
		./src/str_src/split.c \
		./src/get_next_line_func/get_next_line.c \
		./src/get_next_line_func/get_next_line_utils.c \
		./src/draw/utils.c \
		./src/draw/utils2.c \
		./src/draw/vector.c \
		./src/draw/ray_casting.c \
		./src/key_action.c \
		./src/wall_check.c \
		./src/draw/get_texture_color.c \
		./src/minimap/minimap.c

LIBFT = libft.a
LIBFTDIR = ./libft
NAME = cub3D
INCLUDE = -I./include
OBJS = $(SRCS:.c=.o)

ifneq "$(findstring d, $(MAKECMDGOALS))" ""
	CC += -fsanitize=address
endif

MLXLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	make -j -C ${LIBFTDIR}
	make -j -C ./mlx 
	$(CC) $(OBJS) $(INCLUDE) $(MLXLIB) -o $(NAME) ${LIBFTDIR}/${LIBFT}

%.o:%.c
	$(CC) -Imlx $(INCLUDE) -c $< -o $@ -g

clean:
	make clean -C ./mlx
	rm -rf $(OBJS) $(BONUS_OBJS)
	rm -f ${LIBFTDIR}/*.o

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)
	rm -f ${LIBFTDIR}/${LIBFT}

re: fclean all

# debug
d:	fclean all
