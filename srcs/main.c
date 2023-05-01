/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 21:17:12 by siwolee           #+#    #+#             */
/*   Updated: 2023/05/01 21:23:07 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx/mlx.h"
#include "vec3.h"
#include "math.h"

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
	t_world	world;
	t_mlx	mlx;
	
	fd = file_check(ac, av);
	world = parse(fd);
	init_mlx(&mlx);
	draw(&mlx, &world);
	mlx_key_hook(mlx.win, &key_press, &app);
	mlx_loop(&mlx);
	return (0);
}