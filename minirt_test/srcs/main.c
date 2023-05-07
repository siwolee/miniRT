/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:03:04 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 15:06:18 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define WIDTH 1200
#define HEIGHT 600

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	image;
}t_vars;

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

t_point ray_at(t_ray *r, double t)
{
	t_point	temp;

	temp = v_add(r->origin, v_mul_n(r->direction, t));

	return (temp);
}

t_color ray_color(t_scene *scene)
{

	double	t;
	t_vec	n;

	scene->rec = record_init();
	if (hit(scene->world, scene->ray, scene->rec))
		return (phong_lighting(scene));
	else
	{
		t = 0.5 * (scene->ray.dir.y + 1.0);
		return (v_add(v_mul_n(v_create(1, 1, 1), 1.0 - t), v_mul_n(v_create(0.5, 0.7, 1.0), t)));
	}
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray   ray;

	t_vec  horizontal;
	t_vec  vertical;
	t_point   viewport_point;

	ray.origin = cam->origin; // 0, 0, 0

	horizontal = v_mul_n(cam->right_normal, u);
	vertical = v_mul_n(cam->up_normal, v);
	viewport_point = v_add(cam->left_bottom, horizontal);
	viewport_point = v_add(viewport_point, vertical);

	ray.direction = unit_vecter(v_sub(viewport_point, ray.origin));
	return (ray);
}

float	get_tan(float degree)
{
	static const float	radian = M_PI / 180;

	return (tan(degree * radian));
}

t_camera    camera(t_point orig, t_vec dir)
{
	t_camera    cam;
	t_vec     vec_y;
	t_vec     vec_z;
	t_vec     temp;

	vec_y = v_create(0.0, 1.0, 0.0);
	vec_z = v_create(0.0, 0.0, -1.0);

	cam.origin = orig;
	cam.dir = unit_vecter(dir);
	cam.fov = 90;
	if (length(v_cross(vec_y, cam.dir)))
		cam.right_normal = unit_vecter(v_cross(cam.dir, vec_y));
	else
		cam.right_normal = unit_vecter(v_cross(cam.dir, vec_z));

	cam.up_normal = unit_vecter(v_cross(cam.right_normal, cam.dir));
	cam.focal_len = (float)WIDTH / 2 / get_tan(cam.fov / 2);

	temp = v_add(cam.origin, v_mul_n(cam.dir, cam.focal_len));
	temp = v_sub(temp, v_mul_n(cam.right_normal, -(float)(WIDTH - 1)/ 2));
	temp = v_sub(temp, v_mul_n(cam.up_normal, -(float)(HEIGHT - 1)/ 2));
	cam.left_bottom = temp;
	// printf("%lf\n",cam.right_normal.x);
	// printf("%lf\n",cam.up_normal.x);
	// printf("%lf\n",cam.left_bottom.x);
	return (cam);
}

int	main(void)
{
	int     i;
	int     j;

	t_color    pixel_color;
	t_camera    cam;
	t_ray       ray;
	t_object	*world;
	t_scene		*scene;

	scene = scene_init();

	t_vars vars;
	t_data image;

	cam = camera(v_create(0, 0, 0), v_create(1, 1, 1));//벡터 원원점 , 벡벡터 방방향향
	world = object(SP, sphere(v_create(0, 0, -5), 2));
	// oadd(&world, object(SP, sphere(v_create(2, 0, -5), 10)));
	// oadd(&world, object(SP, sphere(v_create(0, -1000, 0), 990)));

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello miniRT!");
  	image.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT); // 이미지 객체 생성
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian); // 이미지 주소 할당

	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
	   while (i < WIDTH)
		{
			ray = ray_primary(scene->camera, i, j);
			pixel_color = ray_color(scene);
			// write_color(pixel_color);
			my_mlx_pixel_put(&image, i, HEIGHT - 1 - j, create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, pixel_color.z * 255.999));
			++i;
		}
		--j;
	}

	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);

	return (0);
}
