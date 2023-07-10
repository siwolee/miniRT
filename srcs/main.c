/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:44:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/10 22:03:36 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

void	file_check(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		exit_error(ERROR_NO_INPUT);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		exit_error(ERROR_READFILE);
	}
	close(fd);
}

//check_if it's rt file
void	check_rt(char *str)
{
	char	*retline;

	retline = ft_strnstr(str + ft_strlen(str) - 3, ".rt", 3);
	if (retline == NULL)
	{
		perror("it's not .rt file");
		exit(1);
	}
}

//erase before submit
void	eeee(void)
{
	system("leaks minirt");
}

int	main(int ac, char **av)
{
	t_vars	vars;

	file_check(ac, av);
	check_rt(av[1]);
	vars.filename = av[1];
	vars.scene = scene_init();
	readmap(&vars.scene, av[1]);
	ft_init_mlx(&vars, &vars.scene, &vars.image);
	ft_draw(&vars.scene, &vars.image);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &key_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

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
