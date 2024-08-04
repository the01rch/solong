# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: redrouic <redrouic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/23 17:13:54 by redrouic          #+#    #+#              #
#    Updated: 2024/08/04 19:46:11 by redrouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= src/main.c			 \
			  src/game.c		 \
			  src/parsing.c		 \
			  src/utils.c		 \
			  src/free.c		 \
			  src/gnl.c		\
			  src/gest_moves.c		\
			  src/flood_fill.c		 \
			  src/find_player.c		 \
			  src/gest_err.c		 \

OBJS		=	$(SRCS:.c=.o)

NAME		=	so_long

CC			=	cc -g3

FLAGS		=	-Wall -Wextra -Werror

MLX			= 	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

RM			=	rm -f

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -c $< -o $@

all:	clone_mlx	$(NAME)

$(NAME):	$(OBJS)
	@make -C ./mlx_linux
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)	

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)
	$(RM) -r mlx_linux

clone_mlx:
	@echo "Cloning minilibx-linux..."
	@if [ -d "mlx_linux" ]; then echo "Mlx already imported in the project.";\
		else git clone --quiet https://github.com/42Paris/minilibx-linux.git mlx_linux; fi

re:		fclean all

.PHONY:		all clean fclean re
