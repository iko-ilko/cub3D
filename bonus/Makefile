CC = cc  -g3 -Wall -Wextra -Werror
SRCS = ./src/main_bonus.c \
		./src/preprocess/preprocess_bonus.c \
		./src/preprocess/parse_map_bonus.c \
		./src/preprocess/convert_map_info_bonus.c \
		./src/preprocess/check_map_bonus.c \
		./src/preprocess/utils_bonus.c \
		./src/str_src/str_func1.c \
		./src/str_src/str_func2.c \
		./src/str_src/split.c \
		./src/get_next_line_func/get_next_line.c \
		./src/get_next_line_func/get_next_line_utils.c \
		./src/draw/utils_bonus.c \
		./src/draw/utils2_bonus.c \
		./src/draw/vector_bonus.c \
		./src/draw/ray_casting_bonus.c \
		./src/key_action_bonus.c \
		./src/wall_check_bonus.c \
		./src/draw/get_texture_color_bonus.c \
		./src/minimap/minimap_bonus.c

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
