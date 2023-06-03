/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:19:51 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/03 19:45:44 by juhyulee         ###   ########.fr       */
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
	t_cylinder	*cy;
	t_cy_temp	*temp;
	double		hit_height;

	temp = malloc(sizeof(t_cy_temp));
	cy = cy_obj->element;
	cy_temp_struct(temp, cy, ray);
	if (temp->discriminant < 0)
		return (free_temp(temp, 0));
	if (temp->root < rec->tmin || rec->tmax < temp->root)
	{
	temp->root = (-temp->half_b + temp->sqrtd) / temp->a;
		if (temp->root < rec->tmin || rec->tmax < temp->root)
			return (free_temp(temp, 0));
	}
	hit_height = cy_boundary(cy, ray_at(ray, temp->root));
	if (!hit_height)
		return (free_temp(temp, 0));
	rec->t = temp->root;
	rec->p = ray_at(ray, temp->root);
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (free_temp(temp, 1));
}
