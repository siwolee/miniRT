LIBMLX = ./mlx/libmlx.a

all : $(LIBMLX)
	gcc test.c -L./mlx -lmlx
 
$(LIBMLX) :
	@make -C ./mlx
