# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 17:53:40 by juhyulee          #+#    #+#              #
#    Updated: 2023/05/28 17:25:33 by juhyulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./srcs/main.c \
		./srcs/mlx.c \
		./srcs/mlx1.c \
		./srcs/vecter.c \
		./srcs/vecter1.c \
		./srcs/vecter2.c \
		./srcs/vecter3.c \
		./srcs/camera.c \
		./srcs/ray.c \
		./srcs/ray1.c \
		./srcs/sphere.c \
		./srcs/object.c \
		./srcs/phong.c \
		./srcs/plane.c \
		./srcs/cylinder.c \
		./srcs/cylinder1.c \
		./srcs/parse.c \
		./srcs/parse1.c \
		./srcs/parse2.c \
		./srcs/parse3.c \

OBJS = $(SRCS:.c=.o)
LMLX = -L./mlx -lmlx -framework OpenGL -framework Appkit

LIBFT = ./libft/libft.a
HEADER = -I./header
NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm -f

all : 		$(NAME)

$(NAME) :	$(OBJS) $(LIBFT)
			$(CC) $(HEADER) $(CFLAGS) $(LIBFT) $(LMLX) \
			$(SRCS) -o $(NAME)

%.o : %.c
			$(CC) $(HEADER) $(CFLAGS) -c $^ -o $@

$(LIBFT) :
			make -C ./libft

clean :
			make -C ./libft fclean
			$(RM) $(OBJS)

fclean :	clean
			rm -rf miniRT.dSYM
			$(RM) $(NAME)

re :		fclean all

.PHONY : all clean fclean re bonus
