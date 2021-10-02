SRCS		= arithmetic.c checkers.c painting.c start.c

OBJS		= ${SRCS:.c=.o}

HDRS		= fractol.h

GCC			= gcc -Wall -Wextra -Werror

FLAGS		= -Imlx -framework OpenGl -framework AppKit

NAME		= fractol

LIB			= ./minilibx_opengl_20191021/

LIB.a		= ${LIB}libmlx.a

all:		${NAME}

%.o:		%.c ${HDRS}
			${GCC} -c -o $@ $<

$(NAME): 	complib ${OBJS}
			@${GCC} ${FLAGS} ${OBJS} ${LIB.a} -o ${NAME}

complib:
			@cd ${LIB} && ${MAKE}

re:			fclean all

clean:
			rm -f ${OBJS}
			@cd ${LIB} && ${MAKE} clean

fclean:		clean
			rm -f ${NAME}

.PHONY:		all re clean fclean
