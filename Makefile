LIBMLX = ./mlx/libmlx.a

MFLAG = -Lmlx -lmlx -framework OpenGL -framework AppKit

CPP_SRCS = cpp/*.cpp
CPP_INCS = cpp/*.hpp
CPP = g++
CPPFLAGS = -std=c++11
CPPTEST = ./tt

all : $(LIBMLX)
	gcc -Lmlx -lmlx -framework OpenGL -framework AppKit test.c vec3.c -fsanitize=address -g3

cpp : $(CPPTEST)

$(CPPTEST) :
	$(CPP) $(CPP_SRCS) $(CPPFLAGS) -o $(CPPTEST)

	
$(LIBMLX) :
	@make -C ./mlx
