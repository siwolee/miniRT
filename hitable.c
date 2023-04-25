/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:42:44 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/25 16:19:12 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"

//물체들을 돌면서 맞았는지 아닌지 판별하는 함수. 결과값은 rec에 저장
t_bool	hit(t_hitable *node, const t_ray *r, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_bool			hit_anything = FALSE;
	double			closest_so_far = t_max;

	while (node)
	{
		// 순서대로 넣기 때문에 아직 비교는 안하고 있음
		if (hit_whatever(node->data, r, &temp_rec))
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t;
			hit_record_dup(&temp_rec, rec);
		}
	}
	return (hit_anything);
}

//hit record 복사 함수 
void	hit_record_dup(t_hit_record *temp, t_hit_record *rec)
{
	if (!temp || !rec)
		return ;
	rec->t = temp->t;
	rec->p = temp->p;
	rec->normal = temp->normal;
}

// type별로 광선 맞았는지 아닌지 판별하게 분류하는 함수. 리턴값은 동일하게 t_bool
t_bool	hit_whatever(t_hitable *node, t_hit_record *rec, t_ray *r, float t_min, float t_max)
{
	// if (node->type == PLANE)
	// {
	// 	return (hit_plane(r, t_min, t_max, rec, node->data));
	// }
	if (node->type == SPHERE)
	{
		return (hit_sphere(r, rec, node->data));
	}
// 	else if (node->type == CYLINDER)
// 	{
// 		return (hit_cylinder(r, t_min, t_max, rec, node->data));
// 	}
}

// 구에서 만약에 맞았을 경우, 결과값을 hit_record에 저장해주는 함수
t_bool	hit_record_init_sphere(t_hit_record *rec, t_ray *r, float temp, float radius)
{
	rec->t = temp;
	rec->p = r->ray_at(rec->t);
	rec->normal = (rec->p - center) / radius;
	return (TRUE);
}

//구에 맞는지 판별하는 함수 - 정리필요
t_bool		hit_sphere(const t_ray *r, t_hit_record *rec, t_sphere *sphere)
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
		return (FALSE);
	temp = (- b - sqrt(b * b - a * c)) / a;
	if (temp < r->t_max && temp > r->t_min)
		return (hit_record_init_sphere(rec, temp, radius));
	temp = (- b + sqrt(b * b - a * c)) / a;
	if (temp < r->t_max && temp > r->t_min)
		return (hit_record_init_sphere(rec, temp, radius));
	return (FALSE);
}
