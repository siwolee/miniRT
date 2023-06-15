/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:22:02 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/15 15:20:56 by siwolee          ###   ########.fr       */
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

// ERROR_NO_INPUT,
// ERROR_CANNOT_OPEN_FILE,
// ERROR_FILE_TYPE,
// ERROR_PARSE,
// ERROR_NO_ELEMENT, ->>no exit
// ERROR_NO_CAMERA,
// ERROR_READFILE,
// ERROR_NO_CAMERA_INPUT
void	exit_error(int code)
{
	if (code == ERROR_NO_ELEMENT)
	{
		printf("ERROR : no element\n");
		return ;
	}
	if (code == ERROR_NO_INPUT)
		printf("ERROR : no file input\n");
	else if (code == ERROR_READFILE)
		printf("ERROR : cannot open file\n");
	else if (code == ERROR_FILE_TYPE)
		printf("ERROR : file type is not\n");
	else if (code == ERROR_PARSE)
		printf("ERROR : parsing error\n");
	else if (code == ERROR_NO_CAMERA)
		printf("ERROR : camera is unvalid\n");
	else if (code == ERROR_NO_CAMERA_INPUT)
		printf("ERROR : map file has no camera\n");
	else
		printf("ERROR : error not specified yet : %d\n", code);
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
		exit_error(ERROR_READFILE);
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
	printf("CAM : switched to cam %d\n", sc->cam_now->num);
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
	printf("CAM : switched to cam %d\n", sc->cam_now->num);
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
