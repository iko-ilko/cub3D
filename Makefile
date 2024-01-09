CC = cc -g3
# -Wall -Wextra -Werror
SRCS = ./src/main.c \
		./src/preprocess.c \
		./src/parse_map.c \
		./src/convert_map_info.c \
		./src/check_map.c \
		./src/utils.c \
		./src/str_src/str_func1.c \
		./src/str_src/str_func2.c \
		./src/str_src/split.c \
		./src/get_next_line_func/get_next_line.c \
		./src/get_next_line_func/get_next_line_utils.c \

NAME = cub3D
INCLUDE = -I./include
OBJS = $(SRCS:.c=.o)

ifneq "$(findstring d, $(MAKECMDGOALS))" ""
	CFLAGS += -g3 -fsanitize=address
endif

# BONUS_SRCS =
# BONUS_NAME = so_long_bonus
# BONUS_OBJS = $(BONUS_SRCS:.c=.o) 

MLXLIB = -Lmlx -lmlx -framework OpenGL -framework Appkit

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	make -C ./mlx 
	$(CC) $(OBJS) $(INCLUDE) $(MLXLIB) -o $(NAME)

# $(BONUS_NAME): $(BONUS_OBJS)
# 	make -C ./mlx 
# 	$(CC) $(BONUS_OBJS) $(MLXLIB) -o $(BONUS_NAME)

%.o:%.c
	$(CC) -Imlx $(INCLUDE) -c $< -o $@ -g

clean:
	make clean -C ./mlx
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME)

re: fclean all

# debug
d: fclean all
