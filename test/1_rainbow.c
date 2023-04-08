#include <stdio.h>
#include "mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include "vec3.h"

// basic 1 : code making rainbow

# define PIXEL_RGB(x, y, z) (x * 256 * 256 + y * 256 + z)

int	pixel_color(double x, double y, double z)
{
	int ir = 255.999 * x;
	int ig = 255.999 * y;
	int ib = 255.999 * z;

	return (PIXEL_RGB(ir, ig, ib));
}
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

#define IMAGE_WIDTH 1000
#define IMAGE_HEIGHT 1000

int main(void)
{
	const int image_width = IMAGE_WIDTH; //size
	const int image_height = IMAGE_HEIGHT;

	t_mlx app;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, 1000, 1000, "rainbow");
	app.img = mlx_new_image(app.mlx, image_width, image_height);
	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);

	write(2, "Scanlines remaining: ", 22);
	int j = 0;
	while (j < image_height)
	{
		int i = 0;
		while (i < image_width)
		{
			int color = pixel_color((double)i / (image_width - 1), (double)j/ (image_height - 1), 0.25);
			app.data[j * IMAGE_WIDTH + i] = mlx_get_color_value(app.mlx, color);
			i++;

		}
		j++;
			write(2, "#", 1);
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
			write(2, "\n", 1);
	mlx_loop(app.mlx);
}
