# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 17:53:40 by juhyulee          #+#    #+#              #
#    Updated: 2023/07/10 16:58:57 by siwolee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
RM = rm -f

SRC = main.c \
		mlx.c \
		mlx1.c \
		vecter.c \
		vecter1.c \
		vecter2.c \
		vecter3.c \
		camera.c \
		ray.c \
		ray1.c \
		sphere.c \
		object.c \
		phong.c \
		plane.c \
		cylinder.c \
		cylinder1.c \
		parse.c \
		parse1.c \
		parse2.c \
		parse3.c \
		free.c 
		# camera_tilt.c
		#  debug.c 

HEADER = -I./header
OBJ_DIR = objs
OBJS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(SRC:.c=.o))
SRC_DIR = srcs
SRCS = $(patsubst %.o,$(SRC_DIR)/%.o,$(SRC:.c=.o))
LMLX_DIR = mlx
LMLX = ./$(LMLX_DIR)/libmlx.a
LMLX_FLAG = -L./$(LMLX_DIR) -lmlx -framework OpenGL -framework Appkit

LIBFT = ./libft/libft.a


all : 		$(NAME)

$(NAME) :	$(LMLX) $(OBJ_DIR) $(OBJS) $(LIBFT) 
			@$(CC) $(HEADER) $(CFLAGS) $(LIBFT) $(LMLX_FLAG) \
			$(OBJS) -o $(NAME)
			@echo "🌹ALL compiled"

$(OBJ_DIR) : 
			@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
			@$(CC) $(HEADER) $(CFLAGS) -c $< -o $@
			@echo "$@ compiling..."

$(LIBFT) :
			@make -sC ./libft
			@echo "💗LIBFT compiled"

$(LMLX)	:
			@make -sC ./$(LMLX_DIR)
			@echo "💗MLX compiled"

clean :
			@make -sC ./libft fclean
			@$(RM) $(OBJS)
			@echo "💔LIBFT and OBJS cleaned"

fclean :	clean
			@rm -rf miniRT.dSYM
			@$(RM) $(NAME)
			@echo "💔fcleaned everything"

re :		fclean all

.PHONY : all clean fclean re bonus
