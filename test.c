#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx/mlx.h"
#include "vec3.h"
#include "ray.h"

double	hit_sphere(t_point *center, double radius, t_ray *r)
{

	t_vec	*oc; //origin to center, ray's vector pointing to sphere
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = vec_vec_min_new(r->origin, center);
	a = vec_dot(r->direction, r->direction);
	b = 2.0 * vec_dot(oc, r->direction);
	c = (vec_dot(oc, oc) - radius * radius);
	free(oc);
	discriminant = b * b - 4 * a * c; //ㅍㅏㄴ벼ㄹ식
	return (discriminant);
}

int ray_color(t_ray *r)
{
	t_point	temp;
	t_color	res;
	t_vec	*unit_direction;
	float	t;

	vec_init(&temp, 0, 0, -1); // 구의 위치
	vec_init(&res, 1, 0, 0); // color
	if (hit_sphere(&temp, 0.5, r) > 0) // 가운데 값 반지름
		return (pixel_color(&res));
	unit_direction = vec_unit_vector(r->direction);
	t = 0.5 * (unit_direction->y + 1.0);
	free(unit_direction);
	vec_init(&res, 1.0, 1.0, 1.0);
	vec_init(&temp, 0.5, 0.7, 1.0);
	vec_mul(&res, 1.0 - t);
	vec_mul(&temp, t);
	vec_vec_add(&res, &temp);
	return (pixel_color(&res));
}

int main() 
{
	//image
	const float	aspect_ratio = 16.0 / 9.0;
	const int image_height = 400;
	const int image_width = image_height * aspect_ratio;

	//mlx
	t_mlx		app;
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, 800, 600, "5.2.1");
	app.img = mlx_new_image(app.mlx, image_width, image_height);
	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);
	
	//camera
	float viewport_height = 2.0;
	float viewport_width = aspect_ratio * viewport_height; //size
	double focal_length = 1.0;

	t_point		origin = {0, 0, 0};
	t_point		horizontal = {viewport_width, 0, 0};
	t_point		vertical = {0, viewport_height, 0};
	t_vec		lower_left_corner = {viewport_width * (-0.5), viewport_height * (-0.5), focal_length * (-1.0)};

	//render
	int j = 0;
	t_ray	r;
	while (j < image_height)
	{
		int i = 0;
		while (i < image_width)
		{
			// ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
			double w, h;
			t_vec *temp;
			w = (horizontal.x  * (double)i) / (image_width - 1);
			h = (vertical.y * (double)j) / (image_height - 1);
			temp = vec_init_new(w, h, 0);
			vec_vec_add(temp, &lower_left_corner);
			vec_vec_min(temp, &origin);
			ray_init_vec(&r, &origin, temp);

			int color = ray_color(&r);
			printf("%d ", color);
			free(temp);
			app.data[j * image_width + i] = mlx_get_color_value(app.mlx, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
	mlx_loop(app.mlx);
}