/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:52:12 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/07 17:51:09 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere	*sphere(t_point center, double radius)
{
	t_sphere	*sp;

	sp = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->center = center;
	sp->radius = radius;
	sp->radius2 = radius * radius;
	return (sp);
}

t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec)
{
	t_sphere_temp	temp;

	temp.sp = (t_sphere *)(sp_obj->element);
	temp.oc = vsub(ray->orig, temp.sp->center);
	temp.a = vlength2(ray->dir);
	temp.half_b = vdot(temp.oc, ray->dir);
	temp.c = vlength2(temp.oc) - temp.sp->radius2;
	temp.discriminant = temp.half_b * temp.half_b - temp.a * temp.c;
	if (temp.discriminant < 0)
		return (FALSE);
	temp.sqrtd = sqrt(temp.discriminant);
	temp.root = (-temp.half_b - temp.sqrtd) / temp.a;
	if (temp.root < rec->tmin || rec->tmax < temp.root)
	{
		temp.root = (-temp.half_b + temp.sqrtd) / temp.a;
		if (temp.root < rec->tmin || rec->tmax < temp.root)
			return (FALSE);
	}
	rec->albedo = sp_obj->albedo;
	rec->t = temp.root;
	rec->p = ray_at(ray, temp.root);
	rec->normal = vdivn(vsub(rec->p, temp.sp->center), temp.sp->radius);
	set_face_normal(ray, rec);
	return (TRUE);
}

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool			hit_anything;
	t_hit_record	temp_rec;

	temp_rec = *rec;
	hit_anything = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, &temp_rec) == TRUE)
		{
			hit_anything = TRUE;
			temp_rec.tmax = temp_rec.t;
			*rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}
