CC = cc -g3
# -Wall -Wextra -Werror
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
		./src/minimap/minimap.c \
		./src/key_event.c \
		./src/draw/utils.c \
		./src/draw/vector.c \
		./src/draw/dda.c \
		./src/draw/plot_line.c \
		# ./src/draw/rotate.c \
		# ./src/draw/bresenham.c \

LIBFT = libft.a
LIBFTDIR = ./libft
NAME = cub3D
INCLUDE = -I./include
OBJS = $(SRCS:.c=.o)

ifneq "$(findstring d, $(MAKECMDGOALS))" ""
	CC += -fsanitize=address
endif

# BONUS_SRCS =
# BONUS_NAME = so_long_bonus
# BONUS_OBJS = $(BONUS_SRCS:.c=.o) 

MLXLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	make -j -C ${LIBFTDIR}
	make -j -C ./mlx 
	$(CC) $(OBJS) $(INCLUDE) $(MLXLIB) -o $(NAME) ${LIBFTDIR}/${LIBFT}

# $(BONUS_NAME): $(BONUS_OBJS)
# 	make -C ./mlx 
# 	$(CC) $(BONUS_OBJS) $(MLXLIB) -o $(BONUS_NAME)

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
