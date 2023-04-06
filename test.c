#include <stdio.h>
#include "mlx/mlx.h"
#include <stdlib.h>

typedef struct s_mlx
{
	void *mlx;
	void *win; 
	void *img;
	int	*data;
	int bpp;
	int size_l;
	int endian;
	int color[3];
}t_mlx;

int main(void)
{
	int image_width = 256;
	int image_height = 256;

	t_mlx app;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, 700, 400, "rainbow");
	app.img = mlx_new_image(app.mlx, image_width, image_height);
	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);

	int j = 0;
	while (j < image_height)
	{
		int i = 0;
		while (i < image_width)
		{
			float r = i / (image_width - 1);
			float g = (image_height - i - 1)/ (image_width - 1);
			float b = 0.25;

			int ir = 255.999 * r;
			int ib = 255.999 * b;
			int ig = 255.999 * g;

			app.color[0]= ir * 256 * 256;
			app.color[1]= ig *256;
			app.color[2]= ib *256;

			int color= app.color[0]+ app.color[1]+app.color[2];
			app.data[j * 256 * i] = mlx_get_color_value(app.mlx, color);
			i++;

		}
		j++;
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
	mlx_loop(app.mlx);
}
