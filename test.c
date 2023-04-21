#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx/mlx.h"
#include "vec3.h"
#include "ray.h"


// bool hit_sphere(const point3& center, double radius, const ray& r) {
//     vec3 oc = r.origin() - center;
//     auto a = dot(r.direction(), r.direction());
//     auto b = 2.0 * dot(oc, r.direction());
//     auto c = dot(oc, oc) - radius*radius;
//     auto discriminant = b*b - 4*a*c;
//     return (discriminant > 0);
// }

int	hit_sphere(t_point *center, double radius, t_ray *r)
{

	t_vec	*oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec_vec_min_new(r->origin, center);
	a = vec_dot(r->direction, r->direction);
	b = 2.0 * vec_dot(oc, r->direction);
	c = vec_dot(oc, oc) - radius * radius;
	free(oc);
	discriminant = b*b - 4*a*c;
	return (discriminant > 0);
}

int ray_color(t_ray *r)
{
	t_point	temp;
	t_color	res;
	t_vec	*unit_direction;
	float	t;

	vec_init(&temp, 0, 0, 1);
	vec_init(&res, 1, 0, 0);
	if (hit_sphere(&temp, 0.5, r))
		return (pixel_color(&res));
	unit_direction = vec_unit_vector(r->direction);
	t = 0.5 * (unit_direction->y + 1.0);
	free(unit_direction);
	vec_init(&res, 1.0, 1.0, 1.0);
	vec_init(&res, 0.5, 0.7, 1.0);
	vec_mul(&res, 1.0 - t);
	vec_mul(&temp, t);
	vec_vec_add(&res, &temp);
	return (pixel_color(&res));
}

// color ray_color(const ray& r) {
//     if (hit_sphere(point3(0,0,-1), 0.5, r))
//         return color(1, 0, 0);
//     vec3 unit_direction = unit_vector(r.direction());
//     auto t = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
// }

// color ray_color(const ray& r) {
//     vec3 unit_direction = unit_vector(r.direction());
//     auto t = 0.5*(unit_direction.y() + 1.0);
//     return ((1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0));
// }

#define IMAGE_RATIO 9/16
#define IMAGE_WIDTH 1680
#define IMAGE_HEIGHT (IMAGE_WIDTH * IMAGE_RATIO)

int main() 
{
	const int image_width = IMAGE_WIDTH; //size
	const int image_height = IMAGE_HEIGHT;

	t_mlx		app;

	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, 2000, 2000, "rainbow");
	app.img = mlx_new_image(app.mlx, image_width, image_height);
	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);
	t_vec	*origin = vec_init_new(0,0,0);
	t_vec	*horizontal = vec_init_new(viewport_width, 0, 0);
	t_vec	*vertical = vec_init_new(viewport_height, 0, 0);

	t_vec *u, *v, *temp;
	temp = vec_div_new(horizontal, 2);
	t_vec	*lower_left_corner;
	u = vec_min_new(origin, temp);
	free(temp);
	temp = vec_min_new(vertical, 2);
	v = vec_min_new(u, temp);
	free(u);
	free(temp);
	temp = vec_init_new(0, 0, focal_length);
	lower_left_corner = vec_min_new(v, temp);
	free(temp);
	// auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

	int j = 0;
	t_ray	r;
	while (j < image_height)
	{
		int i = 0;
		while (i < image_width)
		{
			//ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			u = vec_mul_new(horizontal , double(i) / (image_width-1));
			v = vec_mul_new(vertical , double(i) / (image_height-1));
			temp = vec_add_new(u, v);
			free(u);
			free(v);
			u = vec_add_new(lower_left_corner, temp);
			free(temp);
			temp = vec_min_new(u, origin);
			r = ray_init_vec(origin, temp);

			int color = ray_color(r);
			//pixel_color((double)i / (image_width - 1), (double)j/ (image_height - 1), 0.25);
			app.data[j * IMAGE_WIDTH + i] = mlx_get_color_value(app.mlx, color);
			i++;
			free(temp);
		}
		j++;
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
	mlx_loop(app.mlx);
	free(origin);
	free(horizontal);
	free(vertical);
	free(lower_left_corner);
    //    // Image
    // const auto aspect_ratio = 16.0 / 9.0;
    // const int image_width = 400;
    // const int image_height = static_cast<int>(image_width / aspect_ratio);



    // // Camera

    // auto viewport_height = 2.0;
    // auto viewport_width = aspect_ratio * viewport_height;
    // auto focal_length = 1.0;

    // auto origin = point3(0, 0, 0);
    // auto horizontal = vec3(viewport_width, 0, 0);
    // auto vertical = vec3(0, viewport_height, 0);
    // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // // Render

    // std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // for (int j = image_height-1; j >= 0; --j) {
    //     std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    //     for (int i = 0; i < image_width; ++i) {
    //         auto u = double(i) / (image_width-1);
    //         auto v = double(j) / (image_height-1);
    //         ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    //         color pixel_color = ray_color(r);
    //         write_color(std::cout, pixel_color);
    //     }
    // }

    // std::cerr << "\nDone.\n";

}