/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:34:51 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/24 22:16:07 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITABLE_H
# define HITABLE_H

# include "ray.h"
# include "vec3.h"

typedef struct s_hit_record
{
	float	t;
	t_vec	p;
	t_vec	normal;
}	t_hit_record

typedef struct s_list {
	void			*data; // list 이면 쓰면 되는거 아님?

	struct s_list	*next;
	struct s_list	*prev;

}t_list;

typedef	struct	s_figure_list
{
	void *data;
	

}

int init_hit_record(t_hit_record *rec, t_ray *r, float temp, float radius)
{
	rec->t = temp;
	rec->p = r->point_at_parameter(rec->t);
	rec->normal = (rec->p - center) / radius;
	return (0);
}

int		hit_sphere(const t_ray *r, float t_min, float t_max, hit_record *rec)
{
	t_vec	*oc;
	float	a;
	float	b; // half_b in b*b - 4a*c -> so discriminant is b*b - a*c
	float	c;
	float	discirminant;
	float	temp;
	float	radius;

	radius = (float)(sphere->radius * (0.5));
	oc = vec_vec_sub_new(r->origin, center);
	a = vec_dot(r->direction, r->direction);
	b = vec_dot(oc, r->direction);
	c = vec_dot(oc, oc) - radius * radius;
	discriminant = b * b - a * c;
	if (discriminant < 0)
		return (1);
	temp = (- b - sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min)
		return (init_hit_record(rec, temp, radius));
	temp = (- b + sqrt(b * b - a * c)) / a;
	if (temp < t_max && temp > t_min)
		return (init_hit_record(rec, temp, radius));
	return (1);
}

struct	hita

#endif