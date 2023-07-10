/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:44:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/07 17:29:58 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

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

void	eeee()
{
	system("leaks minirt");
}

int	main(int ac, char **av)
{
	t_vars	vars;
	int		fd;

	fd = file_check(ac, av);
	check_rt(av[1]);
	vars.scene = scene_init();
	readmap(&vars.scene, fd);
	ft_init_mlx(&vars, &vars.scene, &vars.image);
	ft_draw(&vars.scene, &vars.image);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, X_EVENT_KEY_EXIT, 0, &key_destroy, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
