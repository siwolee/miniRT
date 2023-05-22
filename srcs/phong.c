/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 23:09:23 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/22 17:10:34 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	*light_point(t_point light_origin, t_color light_color, double bright_ratio)
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

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_color	diffuse;
	t_vec	light_dir;
	double	kd;
	t_color	specular;
	t_vec	view_dir;
	t_vec	reflect_dir;

	double	light_len;
	t_ray	light_ray;

	double	spec;
	double	ksn;
	double	ks;

	double	brightness;

	light_dir = vsub(light->origin, scene->rec.p);
	light_len = vlength(light_dir);
	light_ray = ray(vadd(scene->rec.p, \
	vmuln(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene->world, light_ray, light_len))
		return (vec(0, 0, 0));
	light_dir = vunit(light_dir);
	kd = fmax(vdot(scene->rec.normal, light_dir), 0.0);
	diffuse = vmuln(light->light_color, kd);

	view_dir = vunit(vmuln(scene->ray.dir, -1));
	reflect_dir = reflect(vmuln(light_dir, -1), scene->rec.normal);
	ksn = 64; //shininess value
	ks = 0.5; //specular strength
	spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
	specular = vmuln(vmuln(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN;
	return (vmuln(vadd(vadd(scene->ambient, diffuse), specular), brightness));
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
