/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:19:51 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/03 20:12:06 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	int			result;

	cy = (t_cylinder *)cy_obj->element;
	result = 0;
	result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
	result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
	result += hit_cylinder_side(cy_obj, ray, rec);
	if (result > 0)
		return (TRUE);
	else
		return (FALSE);
}

void	cy_temp_struct(t_cy_temp *temp, t_cylinder *cy, t_ray *ray)
{
	temp->u = ray->dir;
	temp->o = cy->dir;
	temp->r = cy->dia / 2;
	temp->delta_p = vsub(ray->orig, cy->center);
	temp->a = vlength2(vcross(temp->u, temp->o));
	temp->half_b = vdot(vcross(temp->u, temp->o), \
	vcross(temp->delta_p, temp->o));
	temp->c = vlength2(vcross(temp->delta_p, temp->o)) - pow(temp->r, 2);
	temp->discriminant = temp->half_b * temp->half_b - temp->a * temp->c;
	temp->sqrtd = sqrt(temp->discriminant);
	temp->root = (-(temp->half_b) - temp->sqrtd) / temp->a;
}

int	free_temp(t_cy_temp	*temp, int i)
{
	free(temp);
	return (i);
}

//leaks ok;
int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	static t_cylinder	*cy;
	static t_cy_temp	temp;
	double				hit_height;

	cy = cy_obj->element;
	cy_temp_struct(&temp, cy, ray);
	if (temp.discriminant < 0)
		return (0);
	if (temp.root < rec->tmin || rec->tmax < temp.root)
	{
	temp.root = (-temp.half_b + temp.sqrtd) / temp.a;
		if (temp.root < rec->tmin || rec->tmax < temp.root)
			return (0);
	}
	hit_height = cy_boundary(cy, ray_at(ray, temp.root));
	if (!hit_height)
		return (0);
	rec->t = temp.root;
	rec->p = ray_at(ray, temp.root);
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}
