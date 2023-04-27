#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx.h"
#include "vec3.h"
#include "ray.h"
#include "hitable.h"


#define COLOR_VAL 1

int key_hook(int keycode, t_mlx *mlx)
{
    if(keycode == 53)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(0);
    }
    return (0);
}

//t_minmax 0.0/MAXFLOAT
//현재 1. 1-1
int ray_color(t_ray *r, t_hitable **world, int w, int h)
{
	t_hit_record	rec;
	t_color			res;
	t_vec			*unit_direction;
	t_vec			temp;
	double 			t;
	
	// return (-1);
	// printf("%d %d \n", w, h);
	if (hit(*world, r, &rec) == TRUE)
	{
		// vec_print(&res);
		// printf("%f %f %f\n", rec.normal.x, rec.normal.y, rec.normal.z);
		// vec_print(&res);
		vec_init(&res, (rec.normal.x + COLOR_VAL) * 0.5, (rec.normal.y \
			+ COLOR_VAL) * 0.5, (rec.normal.z + COLOR_VAL) * 0.5);
		// vec_print(&res);
		// exit(1);
		// vec_print(&res);
		return (pixel_color(&res));
	}
	//background
		unit_direction = vec_unit_vector_new(r->direction);
		t = 0.5 * (unit_direction->y + 1.0);
		free(unit_direction);
		vec_init(&res, 1.0, 1.0, 1.0);
		vec_init(&temp, 0.5, 0.7, 1.0);
		vec_mul(&res, 1.0 - t);
		vec_mul(&temp, t);
		vec_vec_add(&res, &temp);
		return (pixel_color(&res));
}

void readmap(t_main *main, char **av);

int main(int ac, char **av) 
{
	// t_main main;

	// if (ac != 2)
	// 	return (0);
	// //.rt 확장자 체크하는 함수
	// readmap(&main, av);

	//image
	const float	aspect_ratio = 16.0 / 9.0;
	const int image_height = 800;
	const int image_width = image_height * aspect_ratio;

	//mlx
	t_mlx		app;
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, image_width, image_height, "5.2.1");
	app.img = mlx_new_image(app.mlx, image_width, image_height);
	app.data = (int *)mlx_get_data_addr(app.img, &app.bpp, &app.size_l, &app.endian);
	
	//camera
	float viewport_height = 2.0; // 뷰포트의 높이
	float viewport_width = aspect_ratio * viewport_height; //size
	double focal_length = 1.0; // 뷰포트에서 직각으로 카메라까지의 거리

	t_point		origin = {0, 0, 0}; //camera's origin
	t_point		horizontal = {viewport_width, 0, 0}; //y = 2 * 16 / 9 >> 비율 안 지키면 카메라 모양 깨짐
	t_point		vertical = {0, viewport_height, 0}; //x = 2.0
	t_vec		lower_left_corner = {viewport_width * (-0.5), viewport_height * (-0.5), focal_length * (-1.0)}; 
	
	//figure
	t_sphere	sp0;
	vec_init(&(sp0.point), 0.2, 0.2, -1.7);
	sp0.dia = 1; //0.5 이하로 안 보임

	//디아랑 z축에 문제 있음

	t_sphere	sp1;
	vec_init(&(sp1.point), 0, 0, -1.2);
	sp1.dia = 5;

	//hittable list - temporary test
	t_hitable	**world;
	t_hitable	a;
	t_hitable	b;
	world = malloc(sizeof(t_hitable *));
	*world = &a;
	a.data = &sp0;
	a.type = SPHERE;
	a.next = &b;
	b.data = &sp1;
	b.type = SPHERE;
	b.next = NULL;

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
			t_vec direction;
			w = (horizontal.x  * (double)i) / (image_width - 1);
			h = (vertical.y * (double)j) / (image_height - 1);
			vec_init(&direction, w, h, 0);
			vec_vec_add(&direction, &lower_left_corner);
			vec_vec_sub(&direction, &origin);
			ray_init_vec(&r, &origin, &direction);
			int color = ray_color(&r, world, i, j);
			// app.data[j * image_width + i] = mlx_get_color_value(app.mlx, color);
			app.data[j * image_width + i] = color;
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
	mlx_key_hook(app.win, key_hook, &app);
	mlx_loop(app.mlx);
}


// double	hit_sphere(t_point *center, double radius, t_ray *r)
// {

// 	t_vec	*oc; //origin to center, ray's vector pointing to sphere
// 	double	a;
// 	double	hb; // if hb : half_b in b^2 - 4ac 
// 	double	c;
// 	double	discriminant;

// 	oc = vec_vec_sub_new(r->origin, center);
// 	a = vec_dot(r->direction, r->direction);
// 	hb = vec_dot(oc, r->direction); // half b in discriminant
// 	c = (vec_dot(oc, oc) - radius * radius);
// 	free(oc);
// 	discriminant = hb * hb - a * c; //ㅍㅏㄴ벼ㄹ식
// 	if (discriminant < 0)
// 		return (-1.0);
// 	else
// 		return ((- hb - sqrt(discriminant)) / a);
// }

// int ray_color(t_ray *r)
// {5
// 	t_point	temp;
// 	t_point	*N;
// 	t_color	res;
// 	t_vec	*unit_direction;

// 	vec_init(&temp, 0.2, 0.2, -1.2); // 구의 위치
// 	double t = hit_sphere(&temp, 0.5, r);
// 	if (t > 0.0)
// 	{
// 		N = vec_vec_sub_new(ray_at(r, t), &temp); // 단위 길이 벡터, 구성 요소는 -1~1 사이
// 		vec_init(&res, N->x + 0.5, N->y + 0.5, N->z + 0.5); 
// 		// color //why + 1?? 아 -1 부터 시작해서...
// 		// color 4분할 -> 1을 더했을 경우. 
// 		// color 0.5를 더해야 함.
// 		free(N);
// 		return (pixel_color(&res));
// 	} // 가운데 값 반지름

// 	unit_direction = vec_unit_vector_new(r->direction);
// 	t = 0.5 * (unit_direction->y + 1.0);
// 	free(unit_direction);
// 	vec_init(&res, 1.0, 1.0, 1.0);
// 	vec_init(&temp, 0.5, 0.7, 1.0);
// 	vec_mul(&res, 1.0 - t);
// 	vec_mul(&temp, t);
// 	vec_vec_add(&res, &temp);
// 	return (pixel_color(&res));
// }