CC =  cc
CFLAGS = -Wall -Wextra -Werror
OBJS  = $(SRCS:.c=.o)

SRCS = srcs/main.c 	srcs/utils.c
LIBFT = libft.a

LIBFTDIR = ./libft

NAME = cub3d

all : ${NAME}

${NAME} : ${OBJS}
	make -C ${LIBFTDIR}
	cc ${CFLAGS}  -lmlx -framework OpenGL -framework Appkit -lz -o $@ $^ ${LIBFTDIR}/${LIBFT}

.c.o :
	${CC} ${CFLAGS} -c $< -o $@

clean :
	rm -f ${OBJS}
	rm -f ${LIBFTDIR}/*.o

fclean : clean 
	rm -f ${NAME}
	rm -f ${LIBFTDIR}/${LIBFT}

re : fclean all

.PHONY : all bonus clean fclean re
