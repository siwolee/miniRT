# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 17:53:40 by juhyulee          #+#    #+#              #
#    Updated: 2023/05/13 17:07:38 by siwolee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ./srcs/main.c \
		./srcs/vecter.c \
		./srcs/camera.c \
		./srcs/ray.c \
		./srcs/sphere.c \
		./srcs/object.c \
		./srcs/phong.c \
		./srcs/plane.c \
		./srcs/cylinder.c
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
