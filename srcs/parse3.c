/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:16:58 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/10 17:29:21 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	input_light(t_scene *scene, char *str)
{
	char		**split;
	char		**origin;
	char		**color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		exit_error(ERROR_PARSE);
	origin = ft_split(split[1], ',');
	color = ft_split(split[3], ',');
	oadd(&scene->light, object(LIGHT_POINT, light_point(parse_vec(origin), \
	vec(1, 1, 1), ft_atod(split[2])), parse_vec_normalize_color(color)));
	free_split(origin);
	free_split(color);
	free_split(split);
}

void	input_background(t_scene *scene, char *str)
{
	char	**split;
	char	**color_up;
	char	**color_down;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	color_up = ft_split(split[1], ',');
	color_down = ft_split(split[2], ',');
	scene->bgcolor_up = parse_vec_normalize_color(color_up);
	scene->bgcolor_down = parse_vec_normalize_color(color_down);
	free_split(split);
}

void	input_canvas(t_scene *scene, char *str)
{
	int		width;
	int 	height;
	char	**split;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	width = ft_atoi(split[1]);
	height = ft_atoi(split[2]);
	scene->canvas = canvas(width, height);
	free_split(split);
}

//check id infront of line
void	id_check(t_scene *scene, char *str)
{
	if (ft_strncmp(str, "map", 3) == 0)
		input_canvas(scene, str);
	else if (ft_strncmp(str, "bg", 2) == 0)
		input_background(scene, str);
	else if (str[0] == 'A')
		input_ambient(scene, str);
	else if (str[0] == 'C')
		input_camera(scene, str);
	else if (str[0] == 'L')
		input_light(scene, str);
	else if (ft_strncmp(str, "pl", 2) == 0)
		input_plane(scene, str);
	else if (ft_strncmp(str, "sp", 2) == 0)
		input_sphere(scene, str);
	else if (ft_strncmp(str, "cy", 2) == 0)
		input_cylinder(scene, str);
}

// read map from the rt.file and parse into map info
void	readmap(t_scene *scene, char *filename)
{
	char	*str;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		
		{
			perror(filename);
		exit_error(ERROR_READFILE);}
	str = get_next_line(fd);
	if (!str)
		exit_error(ERROR_NO_INPUT);
	convert_space(str);
	while (str != 0)
	{
		id_check(scene, str);
		free(str);
		str = NULL;
		str = get_next_line(fd);
		convert_space(str);
	}
	if (!scene->camera)
		exit_error(ERROR_NO_CAMERA_INPUT);
	free(str);
	close(fd);
}