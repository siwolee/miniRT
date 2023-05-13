#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../mlx/mlx.h"
#include "vec3.h"
#include "ray.h"

double	hit_sphere(t_point *center, double radius, t_ray *r)
{

	t_vec	*oc; //origin to center, ray's vector pointing to sphere
	double	a;
	double	hb; // if hb : half_b in b^2 - 4ac 
	double	c;
	double	discriminant;

	oc = vec_vec_sub_new(r->origin, center);
	a = vec_dot(r->direction, r->direction);
	hb = vec_dot(oc, r->direction); // half b in discriminant
	c = (vec_dot(oc, oc) - radius * radius);
	free(oc);
	discriminant = hb * hb - a * c; //ㅍㅏㄴ벼ㄹ식
	if (discriminant < 0)
		return (-1.0);
	else
		return ((- hb - sqrt(discriminant)) / a);
}

// ray 쏴서 컬러값 int형으로 반환하는 함수
// 구에 부딫히면 판별식 값에 따라 색 그라데이션으로 변함
// 아닐 경우 배경 반환
int ray_color(t_ray *r)
{
	t_point	temp;
	t_point	*N;
	t_color	res;
	t_vec	*unit_direction;

	vec_init(&temp, 0.5, 0, -1); // 구의 위치
	double t = hit_sphere(&temp, 0.5, r);
	if (t > 0.0)
	{
		N = vec_vec_sub_new(ray_at(r, t), &temp); // 단위 길이 벡터, 구성 요소는 -1~1 사이
		vec_init(&res, N->x + 0.5, N->y + 0.5, N->z + 0.5); 
		// color //why + 1?? 아 -1 부터 시작해서...
		// color 4분할 -> 1을 더했을 경우. 
		// color 0.5를 더해야 함.
		free(N);
		return (pixel_color(&res));
	} // 가운데 값 반지름
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
			vec_vec_sub(temp, &origin);
			ray_init_vec(&r, &origin, temp);

			int color = ray_color(&r);
			free(temp);
			app.data[j * image_width + i] = mlx_get_color_value(app.mlx, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(app.mlx, app.win, app.img, 0, 0);
	mlx_loop(app.mlx);
}