/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:06:54 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 15:30:42 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(objs, &light_ray, &rec))
		return (TRUE);
	return (FALSE);
}

t_color	point_light_get(t_scene *scene, t_light *light)
{
	t_color	diffuse;
	t_vec	light_dir;
	double	kd; //difuuse 강도

	t_color	specular;
	double	light_len;
	double	light_ray;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	double	ksn;
	double	ks;

	double	brightness;

	light_dir = v_sub(light->origin, scene->rec.p);
	light_len = length(light_dir);
	light_ray = ray_primary();
	if (in_shadow(scene->world, light_ray, light_len))
		return (v_create(0, 0, 0));
	light_dir = unit_vecter(light_dir);
	kd = fmax(dot(scene->rec.normal, light_dir),0.0);
	diffuse = v_mul_n(light->light_color, kd);

	view_dir = unit_vecter(v_mul_n(scene->ray.direction, -1));
	reflect_dir = reflect(v_mul_n(light_dir, -1), scene->rec.normal);
	ksn = 64; //shininess value
	ks = 0.5; // specular strength
	spec = pow(fmax(dot(view_dir, reflect_dir), 0.0), ksn);
	specular = v_mul_n(v_mul_n(light->light_color, ks), spec);
	return (v_mul_n(v_add(diffuse, specular), brightness));
}

t_color	phong_lighting(t_scene *scene)
{
	t_color	light_color;
	t_object	*lights;

	light_color = v_create(0, 0, 0);
	lights = scene->light;
	while (lights)
	{
		if(lights->type == LIGHT_POINT)
			light_color = v_add(light_color, point_light_get(scene, lights->element));
		lights = lights->next;
	}
	light_color = v_add(light_color, scene->ambient);
	return (v_min(v_mul_v(light_color, scene->rec.albedo), v_create(1, 1, 1)));
}


