LIBMLX = ./mlx/libmlx.a

MFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit

CPP_SRCS = cpp/*.cpp
CPP_INCS = cpp/*.hpp
CPP = clang++
CPPFLAGS = -std=c++11
CPPTEST = ./tt

NAME = aa

all : $(NAME)

$(NAME) : $(LIBMLX)
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit test.c vec3.c -fsanitize=address -g3 -o $(NAME)

cpp : $(CPPTEST)

$(CPPTEST) :
	$(CPP) $(CPP_SRCS) $(CPPFLAGS) -o $(CPPTEST)


fclean :
	rm $(NAME) $(CPPTEST)

re : fclean all
	
$(LIBMLX) :
	@make -C ./mlx

.PHONY : all re cpp fclean