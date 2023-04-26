LIBMLX = ./mlx/libmlx.a
LIBFT = ./libft/libft.a

MFLAG = -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit

CPP_SRCS = cpp/*.cpp
CPP_INCS = cpp/*.hpp
CPP = clang++
CPPFLAGS = -std=c++11
CPPTEST = ./tt

# SRCS = test.c vec3.c ray.c
SRCS = srcs/*.c

NAME = aa

all : $(NAME)

$(NAME) : $(LIBMLX) $(SRCS) $(LIBFT)
	$(CC) $(MFLAG) $(SRCS) -fsanitize=address -g3 -o $(NAME)

ex : $(LIBMLX)
	$(CC) $(MFLAG) ex.c -fsanitize=address -g3 -o $(NAME)


cpp : $(CPPTEST)

$(CPPTEST) :
	$(CPP) $(CPP_SRCS) $(CPPFLAGS) -o $(CPPTEST)


fclean :
	rm $(NAME)

re : fclean all
	
$(LIBMLX) :
	@make -C ./mlx
	cp mlx/libmlx.a ./

$(LIBFT) :
	@make -C ./libft
	

.PHONY : all re cpp fclean