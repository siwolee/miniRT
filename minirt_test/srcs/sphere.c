/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:06:03 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 14:48:24 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere    *sphere(t_point center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

t_bool	hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_sphere	*sp = world->element;
	t_vec	oc;
	t_vec	normal;

	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;

	oc = v_sub(ray->origin, sp->center);
	a = length_squared(ray->direction);
	half_b = dot(oc, ray->direction);
	c = length_squared(oc) - sp->radius2;
	discriminant = (half_b * half_b) - (a * c);
	rec->albedo = world->albedo;

	if (discriminant < 0)
		return (FALSE);

	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
		return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	normal = v_sub(rec->p, sp->center); //법선 벡터
	rec->normal = v_div(normal, sp->radius);
	//set_face_normal(ray, rec);// 카메라가 구의 안쪽에 있을 경우 광선과 법선은 같은 방향을 향하게 된다. 법선과 광선이 반대방향을 향햐도록 확인하는 함수
	return (TRUE);
}

t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	return (hit_result);
}

t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_anything;
	t_hit_record	*temp_rec;

	temp_rec = rec;
	hit_anything = FALSE;
	while (world)
	{
		if (hit_obj(world, ray, temp_rec))
		{
			hit_anything = TRUE;
			temp_rec->tmax = temp_rec->t;
			rec = temp_rec;
		}
		world = world->next;
	}
	return (hit_anything);
}
