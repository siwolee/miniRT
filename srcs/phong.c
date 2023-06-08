/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:09:23 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/08 21:46:03 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	*light_point(t_point light_origin, t_color light_color, \
double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

t_color	phong_lighting(t_scene *scene)
{
	t_color		light_color;
	t_object	*lights;

	light_color = vec(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if (lights->type == LIGHT_POINT)
			light_color = vadd(light_color, \
			point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = vadd(light_color, scene->ambient);
	return (vmin(vmulv(light_color, scene->rec.albedo), vec(1, 1, 1)));
}

void	light_sub(t_light_temp *temp, t_light *light, t_scene *scene)
{
	temp->light_dir = vsub(light->origin, scene->rec.p);
	temp->light_len = vlength(temp->light_dir);
	temp->light_ray = ray(vadd(scene->rec.p, \
	vmuln(scene->rec.normal, EPSILON)), temp->light_dir);
	temp->light_dir = vunit(temp->light_dir);
	temp->kd = fmax(vdot(scene->rec.normal, temp->light_dir), 0.0);
	temp->diffuse = vmuln(light->light_color, temp->kd);
	temp->view_dir = vunit(vmuln(scene->ray.dir, -1));
	temp->reflect_dir = reflect(vmuln(temp->light_dir, -1), scene->rec.normal);
	temp->ksn = 64;
	temp->ks = 0.5;
	temp->spec = pow(fmax(vdot(temp->view_dir, temp->reflect_dir), 0.0), \
	temp->ksn);
	temp->specular = vmuln(vmuln(light->light_color, temp->ks), temp->spec);
	temp->brightness = light->bright_ratio * LUMEN;
}

//leaks ok
t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_light_temp	*temp;
	t_color			color;

	temp = malloc(sizeof(t_light_temp));
	light_sub(temp, light, scene);
	if (in_shadow(scene->world, temp->light_ray, temp->light_len))
	{
		free(temp);
		return (vec(0, 0, 0));
	}
	color = vmuln(vadd(vadd(scene->ambient, temp->diffuse), \
	temp->specular), temp->brightness);
	free(temp);
	return (color);
}

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}
