/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:21:22 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/10 16:59:33 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

//initing mlx canvas values
t_scene	scene_init(void)
{
	t_scene		scene;

	scene.canvas = canvas(600, 400);
	scene.camera = NULL;
	scene.world = NULL;
	scene.light = NULL;
	scene.bgcolor_up = vec(0, 0.7, 1.0);
	scene.bgcolor_down = vec(1, 1, 1);
	return (scene);
}

void	ft_draw(t_scene *scene, t_data *image)
{
	int		i;
	int		j;
	double	u;
	double	v;
	t_color	pixel_color;

	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			scene->ray = ray_primary(scene->cam_now, u, v);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(image, i, scene->canvas.height - 1 - j, \
			create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, \
			pixel_color.z * 255.999));
			++i;
		}
		--j;
	}
}
