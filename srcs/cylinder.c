/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:23:38 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/28 19:01:01 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cylinder	*cylinder(t_point center, t_vec dir, double dia, double height)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->center = center;
	cy->dir = dir;
	cy->dia = dia;
	cy->height = height;
	return (cy);
}

int	cy_boundary(t_cylinder *cy, t_vec at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vdot(vsub(at_point, cy->center), cy->dir);
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (0);
	return (1);
}

t_vec	get_cylinder_normal(t_cylinder *cy, t_vec at_point, double hit_height)
{
	t_point	hit_center;
	t_vec	normal;

	hit_center = vadd(cy->center, vmuln(cy->dir, hit_height));
	normal = vsub(at_point, hit_center);

	return (vunit(normal));
}

int	cap_discrement(double r, float diameter, float root, t_hit_record *rec)
{
	if (fabs(r) < fabs(diameter))
		return (0);
	if (root < rec->tmin || rec->tmax < root)
		return (0);
	return (1);
}

int	hit_cylinder_cap(t_object *cy_obj, t_ray *ray, \
t_hit_record *rec, double height)
{
	t_cylinder	*cy;
	double		r;
	t_vec		circle_center;
	float		root;
	float		diameter;

	cy = cy_obj->element;
	r = cy->dia / 2;
	circle_center = vadd(cy->center, vmuln(cy->dir, height));
	root = vdot(vsub(circle_center, ray->orig), cy->dir) / \
	vdot(ray->dir, cy->dir);
	diameter = vlength(vsub(circle_center, ray_at(ray, root)));

	if (!(cap_discrement(r, diameter, root, rec)))
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->tmax = rec->t;
	if (0 < height)
		rec->normal = cy->dir;
	else
		rec->normal = vmuln(cy->dir, -1);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

void	cy_temp_struct(t_cy_temp *temp, t_cylinder *cy, t_ray *ray)
{
	temp->u = ray->dir;
	temp->o = cy->dir;
	temp->r = cy->dia / 2;
	temp->delta_p = vsub(ray->orig, cy->center);
	temp->a = vlength2(vcross(temp->u, temp->o));
	temp->half_b = vdot(vcross(temp->u, temp->o), vcross(temp->delta_p, temp->o));
	temp->c = vlength2(vcross(temp->u, temp->o)) - pow(temp->r, 2);
	temp->discriminant = temp->half_b * temp->half_b - temp->a * temp->c;
	temp->sqrtd = sqrt(temp->discriminant);
	temp->root = (-temp->half_b - temp->sqrtd) / temp->a;
}

int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder *cy;
	t_cy_temp *temp;

	temp = malloc(sizeof(t_cy_temp));
	// double	a;
	// double	half_b;
	// double	c;
	// t_vec	u;
	// t_vec	o;
	// t_vec	delta_P;
	// double	r;
	// double discriminant;
	// double sqrtd;
	// double root;
	double hit_height;
	cy = cy_obj->element;
	cy_temp_struct(temp, cy, ray);
	// u = ray->dir;
	// o = cy->dir;
	// r = cy->dia / 2;
	// delta_P = vsub(ray->orig, cy->center);
	// a = vlength2(vcross(u, o));
	// half_b = vdot(vcross(u, o), vcross(delta_P, o));
	// c = vlength2(vcross(delta_P, o)) - pow(r, 2);
	// discriminant = half_b * half_b - a * c;
	if (temp->discriminant < 0)
		return (0);
	// sqrtd = sqrt(discriminant);
	// root = (-half_b - sqrtd) / a;
	if (temp->root < rec->tmin || rec->tmax < temp->root)
	{
	temp->root = (-temp->half_b + temp->sqrtd) / temp->a;
		if (temp->root < rec->tmin || rec->tmax < temp->root)
			return (0);
	}
	hit_height = cy_boundary(cy, ray_at(ray, temp->root));
	if (!hit_height)
		return (0);
	rec->t = temp->root;
	rec->p = ray_at(ray, temp->root);
	rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}


