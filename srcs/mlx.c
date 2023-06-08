/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:22:02 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/08 21:40:08 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_init_mlx(t_vars *vars, t_scene *scene, t_data *image)
{
	vars->mlx = mlx_init();
	scene->cam_now = scene->camera;
	vars->win = mlx_new_window(vars->mlx, scene->canvas.width, \
	scene->canvas.height, "miniRT");
	image->img = mlx_new_image(vars->mlx, scene->canvas.width, \
	scene->canvas.height);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, \
	&image->line_length, &image->endian);
}

void	exit_error(int code)
{
	if (code == ERROR_NO_INPUT)
	{
		printf("no file input\n");
	}
	else if (code == ERROR_CANNOT_OPEN_FILE)
		printf("cannot open file\n");
	else if (code == ERROR_PARSE)
		printf("parsing error\n");
	else
		printf("error not specified yet : %d\n", code);
	exit(1);
}

int	file_check(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		exit_error(ERROR_NO_INPUT);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		exit_error(2);
	}
	return (fd);
}

int	key_destroy(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	free_vars(vars);
	printf("EXIT\n");
	exit(0);
}

void	next_cam(t_scene *sc)
{
	if (!sc->cam_now->next)
	{
		printf("NEXT : no camera exits\n");
		return ;
	}
	sc->cam_now = sc->cam_now->next;
}

void	prev_cam(t_scene *sc)
{
	t_camera	*prev;

	if (sc->cam_now == sc->camera)
	{
		printf("PREV : no camera exits\n");
		return ;
	}
	prev = sc->camera;
	while (prev && prev->next != sc->cam_now)
	{
		prev = prev->next;
	}
	sc->cam_now = prev;
}


int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 53 || keycode == X_EVENT_KEY_EXIT)
		key_destroy(vars);
	if (keycode == 0)
		next_cam(&vars->scene);
	else if (keycode == 2)
		prev_cam(&vars->scene);
	else
		return (0);
	ft_draw(&vars->scene, &vars->image);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	return (0);
}
