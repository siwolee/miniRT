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

// int main(void)
// {
// 	const int image_width = 1000;
// 	const int image_height = 1000;

// 	t_mlx app;

// 	app.mlx = mlx_init();
// 	app.win = mlx_new_window(app.mlx, 1000, 1000, "rainbow");
// 	app.img = mlx_new_image(app.mlx, image_width, image_height);
// 	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);

// 	write(2, "Scanlines remaining: ", 22);
// 	int j = 0;
// 	while (j < image_height)
// 	{
// 		int i = 0;
// 		while (i < image_width)
// 		{
// 			int color = pixel_color((double)i / (image_width - 1), (double)j/ (image_height - 1), 0.25);
// 			app.data[j * 1000 + i] = mlx_get_color_value(app.mlx, color);
// 			i++;

// 		}
// 		j++;
// 			write(2, "#", 1);
// 	}
// 	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
// 			write(2, "\n", 1);
// 	mlx_loop(app.mlx);
// }

#include "vec3.h"

void write_color() 
{

}

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return ((1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0));
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}