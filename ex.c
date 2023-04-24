#include "mlx.h"
#include <stdlib.h>
#include <math.h>

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
} t_vec;

typedef	struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	int  *data;
	int		bpp;
	int	size_l;
	int	endian;

	t_vec	color;
	int		int_color;

} t_mlx;

t_vec	make_v(float n)
{
	t_vec v;
	v.x = n;
	v.y = n;
	v.z = n;

	return (v);
}

t_vec	v_mul_n(t_vec v1, float n)
{
	t_vec	result;

	result.x = v1.x * n;
	result.y = v1.y * n;
	result.z = v1.z * n;
	return (result);
}

t_vec	v_mul(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}

float	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	v_sub(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec	v_add(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec	v_div(t_vec v1, float d)
{
	t_vec	result;

	result.x = v1.x / d;
	result.y = v1.y / d;
	result.z = v1.z / d;
	return (result);
}

t_vec	origin(t_vec orig, t_vec dir)
{
	return (orig);
}

t_vec	direction(t_vec orig, t_vec dir)
{
	return (dir);
}
/*
t_vec	ray(t_vec orig, t_vec dir)
{

}

t_vec	at(t_vec orig, t_vec dir, double t)
{
	return (orig + t * dir);
}
*/

void	write_color(t_mlx *app, t_vec c)
{
	int	ir = 255.999 * c.x;
	int	ig = 255.999 * c.y;
	int	ib = 255.999 * c.z;

	app->color.x = ir * 256 * 256;
	app->color.y = ig * 256;
	app->color.z = ib;
	app->int_color = app->color.x + app->color.y + app->color.z;
}

float	length_squared(t_vec e)
{
	return (e.x * e.x + e.y * e.y + e.z * e.z);
}

float length(t_vec e)
{
	return (sqrt(length_squared(e)));
}

t_vec	unit_vector(t_vec v)
{
	return (v_div(v, length(v)));
}

int	hit_sphere(t_vec center, double radius, t_vec origin, t_vec direction)
{
	t_vec oc = v_sub(origin, center);
	float a = dot(direction, direction);
	float b = 2.0 * dot(oc, direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > 0 ? 1 : 0);
}

t_vec	ray_color(t_vec orig, t_vec dir)
{
	t_vec sphere = {0, 0, -1};
	t_vec sphere_color = {1, 0, 0};
	if (hit_sphere(sphere, 0.5, orig, dir))
		return (sphere_color);
	t_vec unit_direction = unit_vector(dir);
	float t = 0.5 * (unit_direction.y + 1.0);
	t_vec a= make_v(1.0);
	t_vec b; b.x = 0.5; b.y = 0.7; b.z = 1.0;
	return (v_add(v_mul_n(a, 1.0 - t), v_mul_n(b, t)));
}

#include <stdio.h>

int	main()
{
	// Image
	const float	aspect_ratio = 16.0 / 9.0;
	const int	image_width = 400;
	const int	image_height = image_width / aspect_ratio;

	// Start mlx
	t_mlx	*app;
	if (!(app = (t_mlx*)malloc(sizeof(t_mlx))))
		return (-1);
	app->mlx_ptr = mlx_init();
	app->win_ptr = mlx_new_window(app->mlx_ptr, 800, 600, "raytracer");
	app->img_ptr = mlx_new_image(app->mlx_ptr, image_width, image_height);
	app->data = (int *)mlx_get_data_addr(app->img_ptr, &app->bpp, &app->size_l, &app->endian);


	// Camera
	float	viewport_height = 2.0;
	float	viewport_width = aspect_ratio * viewport_height;
	float	focal_length = 1.0;

	t_vec	origin = {0,0,0};
	t_vec	horizontal = {viewport_width, 0, 0};
	t_vec	vertical = {0, viewport_height, 0}; t_vec any = {0, 0, focal_length};
	t_vec	lower_left_corner = v_sub(origin, v_add(v_add(v_div(horizontal, 2), v_div(vertical, 2)), any));

	// Render

	int jj = 0;
	int j = image_height - 1;
	while (j >= 0 && jj < image_height)
	{
		int i = 0;
		while (i < image_width)
		{

			float u = (double)i / (image_width - 1);
			float v = (double)j / (image_height - 1);

			t_vec a = origin;
			t_vec b = v_add(lower_left_corner, v_add(v_mul_n(horizontal, u), v_mul_n(v_sub(vertical, origin), v)));
			t_vec pixel_color = ray_color(a, b);
			write_color(app, pixel_color);
			mlx_pixel_put(app->mlx_ptr, app->win_ptr, i, jj, app->int_color);
//			app->data[jj * 400 + i] = app->int_color;

			++i;
		}
		--j;
		++jj; //예제의 점 찍히는 순서를 똑같이 하려고 jj를 따로 만들었음..
	}
//	mlx_put_image_to_window (app->mlx_ptr, app->win_ptr, app->img_ptr, 0, 0);
	mlx_loop(app->mlx_ptr);
}


// double	hit_sphere(t_point *center, double radius, t_ray *r)
// {

// 	t_vec	*oc; //origin to center, ray's vector pointing to sphere
// 	double	a;
// 	double	b;
// 	double	c;
// 	double	discriminant;

// 	oc = vec_vec_min_new(r->origin, center);
// 	a = vec_dot(r->direction, r->direction);
// 	// vec_print(r->direction);
// 	b = 2.0 * vec_dot(oc, r->direction);
// 	c = (vec_dot(oc, oc) - radius * radius);
// 	free(oc);
// 	discriminant = b * b - 4 * a * c; //ㅍㅏㄴ벼ㄹ식
// 	printf("%f   ", discriminant);
// 	return (discriminant);
// }

// int ray_color(t_ray *r)
// {
// 	t_point	temp;
// 	t_color	res;
// 	t_vec	*unit_direction;
// 	float	t;

// 	vec_init(&temp, 0, 0, 0.0); // 구의 위치
// 	vec_init(&res, 1, 0, 0); // color
// 	if (hit_sphere(&temp, 0.01, r) > 0) // 가운데 값 반지름
// 	{
// 		return (pixel_color(&res));
// 	}
// 	unit_direction = vec_unit_vector(r->direction); //여기서 값이 업데이트가 안돼고 있음.. 
// 	t = 0.5 * (unit_direction->y + 1.0);
// 	// printf("%f ", unit_direction->y);
// 	free(unit_direction);
// 	vec_init(&res, 1.0, 1.0, 1.0);
// 	vec_init(&temp, 0.5, 0.7, 1.0);
// 	vec_mul(&res, 1.0 - t);
// 	vec_mul(&temp, t);
// 	vec_vec_add(&res, &temp);
// 	return (pixel_color(&res));
// }


// // color ray_color(const ray& r) {
// //     if (hit_sphere(point3(0,0,-1), 0.5, r))
// //         return color(1, 0, 0);
// //     vec3 unit_direction = unit_vector(r.direction());
// //     auto t = 0.5*(unit_direction.y() + 1.0);
// //     return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
// // }

// // color ray_color(const ray& r) {
// //     vec3 unit_direction = unit_vector(r.direction());
// //     auto t = 0.5*(unit_direction.y() + 1.0);
// //     return ((1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0));
// // }

// int main() 
// {
// 	//image
// 	const float	aspect_ratio = 16.0 / 9.0;
// 	const int image_height = 400;
// 	const int image_width = image_width / aspect_ratio;

// 	//mlx
// 	t_mlx		app;
// 	app.mlx = mlx_init();
// 	app.win = mlx_new_window(app.mlx, 800, 600, "5.2.1");
// 	app.img = mlx_new_image(app.mlx, image_width, image_height);
// 	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);
	
// 	//camera
// 	float viewport_height = 2.0;
// 	float viewport_width = aspect_ratio * viewport_height; //size
// 	double focal_length = 1.0;

// 	t_point		origin = {0, 0, 0};
// 	t_point		horizontal = {viewport_width, 0, 0};
// 	t_point		vertical = {0, viewport_height, 0};
// 	t_vec		lower_left_corner = {viewport_width * (-0.5), viewport_height * (-0.5), focal_length * (-1.0)};

// 	//render
// 	int jj = 0;
// 	int j = image_height - 1;
// 	t_ray	r;
// 	while (j >= 0 && jj < image_height)
// 	{
// 		int i = 0;
// 		while (i < image_width)
// 		{
// 			// ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
// 			double w, h;
// 			t_vec *temp;
// 			w = (horizontal.x  * (double)i) / (image_width - 1);
// 			h = (vertical.y * (double)j) / (image_height - 1);
// 			temp = vec_init_new(w, h, 0);
// 			vec_vec_add(temp, &lower_left_corner);
// 			vec_vec_min(temp, &origin);
// 			ray_init_vec(&r, &origin, &temp);

// 			int color = ray_color(&r);
// 			// write_color(&app, color);
// 			mlx_pixel_put(app.mlx, app.win, i, jj, color);
// 			app.data[jj * image_width + i] = color;
// 			// mlx_get_color_value(app.mlx, color);
// 			free(temp);
// 			i++;
// 		}
// 		--j;
// 		++jj;
// 	}
// 	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
// 	mlx_loop(app.mlx);
// }