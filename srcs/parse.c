/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:07:25 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/10 22:09:13 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

void	input_cylinder(t_scene *scene, char *str)
{
	char		**split;
	char		**point;
	char		**vec;
	char		**color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || !split[3] || \
	!split[4] || !split[5] || split[6])
		exit_error(ERROR_PARSE);
	point = ft_split(split[1], ',');
	vec = ft_split(split[2], ',');
	color = ft_split(split[5], ',');
	oadd(&scene->world, object(CY, cylinder(parse_point(point), \
		parse_vec(vec), ft_atod(split[3]), ft_atod(split[4])), \
		parse_vec_normalize_color(color)));
	free_split(point);
	free_split(vec);
	free_split(color);
	free_split(split);
}

void	input_sphere(t_scene *scene, char *str)
{
	char	**split;
	char	**center;
	double	dia;
	char	**color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		exit_error(ERROR_PARSE);
	center = ft_split(valid_parse_vec(split[1]), ',');
	dia = ft_atod(split[2]);
	color = ft_split(valid_parse_vec(split[3]), ',');
	oadd(&scene->world, object(SP, sphere(parse_point(center), \
			dia), parse_vec_normalize_color(color)));
	free_split(center);
	free_split(color);
	free_split(split);
}

void	input_camera(t_scene *scene, char *str)
{
	char		**tp;
	char		**orig;
	char		**dir;
	t_camera	*cam;

	tp = ft_split(str, ' ');
	if (!tp[0] || !tp[1] || !tp[2] || !tp[3] || tp[4])
		exit_error(ERROR_PARSE);
	orig = ft_split(valid_parse_vec(tp[1]), ',');
	dir = ft_split(valid_parse_vec(tp[2]), ',');
	if (!scene->camera)
		scene->camera = camera(parse_point(orig), parse_vec(dir), ft_atod(tp[3]), \
		(float)scene->canvas.width / (float) scene->canvas.height);
	else
	{
		cam = scene->camera;
		while (cam->next)
			cam = cam->next;
		cam->next = camera(parse_point(orig), parse_vec(dir), ft_atod(tp[3]), \
		(float)scene->canvas.width / (float) scene->canvas.height);
		cam->next->num = cam->num + 1;
	}
	free_split(orig);
	free_split(dir);
	free_split(tp);
}

void	input_ambient(t_scene *scene, char *str)
{
	char	**split;
	char	**color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	color = ft_split(split[2], ',');
	scene->ambient = vmuln(parse_vec_normalize_color(color), \
					ft_atod(split[1]));
	free_split(color);
	free_split(split);
}

void	input_plane(t_scene *scene, char *str)
{
	char	**split;
	char	**center;
	char	**dir;
	char	**color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		exit_error(ERROR_PARSE);
	center = ft_split(valid_parse_vec(split[1]), ',');
	dir = ft_split(valid_parse_vec(split[2]), ',');
	color = ft_split(valid_parse_vec(split[3]), ',');
	if (!scene->world)
		scene->world = object(PL, plane(parse_point(center), \
		parse_vec(dir)), parse_point(color));
	else
		oadd(&scene->world, object(PL, plane(parse_point(center), \
		parse_vec(dir)), parse_vec_normalize_color(color)));
	free_split(center);
	free_split(dir);
	free_split(color);
	free_split(split);
}
