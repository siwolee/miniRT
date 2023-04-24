LIBMLX = ./mlx/libmlx.a

MFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit

CPP_SRCS = cpp/*.cpp
CPP_INCS = cpp/*.hpp
CPP = clang++
CPPFLAGS = -std=c++11
CPPTEST = ./tt

SRCS = test.c vec3.c ray.c

NAME = aa

all : $(NAME)

$(NAME) : $(LIBMLX) $(SRCS)
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit $(SRCS) -fsanitize=address -g3 -o $(NAME)

ex : $(LIBMLX)
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit ex.c -fsanitize=address -g3 -o $(NAME)


cpp : $(CPPTEST)

$(CPPTEST) :
	$(CPP) $(CPP_SRCS) $(CPPFLAGS) -o $(CPPTEST)


fclean :
	rm $(NAME)

re : fclean all
	
$(LIBMLX) :
	@make -C ./mlx

.PHONY : all re cpp fclean