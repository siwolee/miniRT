/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:44:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/08 19:57:01 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

void	check_len(char *str)
{
	char	*retline;

	retline = ft_strnstr(str + ft_strlen(str) - 3, ".rt", 3);
	if (retline == NULL)
	{
		ft_printf("it's not .rt file");
		exit(0);
	}
}

void	eeee()
{
	system("leaks minirt");
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		fd;

	fd = file_check(ac, av);
	vars.scene = scene_init();
	check_len(av[1]);
	readmap(&vars.scene, fd);
	ft_init_mlx(&vars, &vars.scene, &vars.image);
	ft_draw(&vars.scene, &vars.image);
	// system("leaks miniRT");
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &key_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
