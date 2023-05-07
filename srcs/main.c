/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:17:12 by siwolee           #+#    #+#             */
/*   Updated: 2023/05/02 16:48:32 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "vec3.h"
#include <math.h>
#include "define.h"

#define ASPECT_RATIO (16 / 9)

t_cam	*new_camera(t_point origin, t_point direction, double degree, double aspect)
{
	t_cam	*cam;
	float	theta;
	float	half_height;
	float	half_width;

	cam = malloc(sizeof(t_cam));
	cam->origin = v_create(origin.x, origin.y, origin.z);
	cam->direction = v_create(direction.x, direction.y, direction.z);
	theta = vfov * M_PI / 180;
	half_height = tan(theta / 2);
	half_width = aspect * half_height;
	cam->lower_left_corner = v_create(half_width * (-1), half_height * (-1), -1.0);
	cam->horizontal = v_create(2 * half_width, 0, 0);
	cam->vertical = v_create(0, 2 * half_height, 0);
}

t_scene	temp_init(void)
{
	t_scene		sc;
	t_sphere	*sp1;

	sp1 = malloc(sizeof(t_sphere));
	sp1->origin = v_create(0, 1, -1);
	sp1->radius = 1;
	sp1->direction = v_create(0, 0, -2);

	sc.cam = new_camera({0, 0, 0}, {0, 0, -1}, 70, ASPECT_RATIO);
	sc.hitable.data = sp1;
	sc.hitable.type = TYPE_CYLINDER;
	sc.hitable.next = 0;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, image_width, image_height, "raytracer");
	mlx->img = mlx_new_image(mlx->mlx, image_width, image_height);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_l, &mlx->endian);
}

init_camera()
{

}

get_camera_ray(t_scene *scene, double w, double h)
{

}

void	draw(t_mlx *mlx, t_scene *scene)
{
	double	h;
	double	w;
	t_ray	ray;

	h = scene->image_height - 1;
	while (h >= 0)
	{
		w = 0;
		while (w < scene->image_width)
		{
			ray = get_camera_ray(scene, w, h);
			color = ray_color(&r)
			mlx->data[j * scene->image_width + i] = color;
			w++;
		}
		h--;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 13)
		printf("W\n");
	else if (keycode == 1)
		printf("S\n");
	else if (keycode == 0)
		printf("A\n");
	else if (keycode == 2)
		printf("D\n");
	else if (keycode == 53)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		exit(0);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_scene	scene;
	t_mlx	mlx;
	
	fd = file_check(ac, av);
	scene = parse(fd);
	init_mlx(&mlx);
	draw(&mlx, &scene);
	mlx_key_hook(mlx.win, &key_press, &app);
	mlx_loop(&mlx);
	return (0);
}