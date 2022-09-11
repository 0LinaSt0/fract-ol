# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msalena <msalena@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/02 17:38:42 by msalena           #+#    #+#              #
#    Updated: 2021/10/02 17:38:42 by msalena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= arithmetic.c checkers.c painting.c start.c

OBJS		= ${SRCS:.c=.o}

HDRS		= fractol.h

GCC			= gcc -Wall -Wextra -Werror

FLAGS		= -Imlx -framework OpenGl -framework AppKit

NAME		= fractol

LIB			= ./minilibx_opengl_20191021/

LIB.a		= ${LIB}libmlx.a

all:		${NAME}

%.o:		%.c ${HDRS} Makefile
			${GCC} -c -o $@ $<

$(NAME): 	complib ${OBJS} Makefile
			@${GCC} ${FLAGS} ${OBJS} ${LIB.a} -o ${NAME}

complib:
			@cd ${LIB} && ${MAKE}

re:			fclean all

clean:
			rm -f ${OBJS}
			@cd ${LIB} && ${MAKE} clean

fclean:		clean
			rm -f ${NAME}

norm:
			@norminette $(SRCS) $(HDRS)

.PHONY:		all re clean fclean
