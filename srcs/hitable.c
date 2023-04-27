/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:42:44 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/27 21:31:25 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "vec3.h"

//물체들을 돌면서 맞았는지 아닌지 판별하는 함수. 결과값은 rec에 저장
t_bool	hit(t_hitable *node, t_ray *r, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_bool			hit_anything = FALSE;
	double			closest_so_far;

	while (node)
	{
		// 순서대로 넣기 때문에 아직 비교는 안하고 있음
		if (hit_whatever(node, &temp_rec, r) == TRUE)
		{
			hit_anything = TRUE;
			closest_so_far = temp_rec.t;
			hit_record_dup(&temp_rec, rec);
		}
		node = node->next;
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
t_bool	hit_whatever(t_hitable *node, t_hit_record *rec, t_ray *r)
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
	return (FALSE);
}

// 구에서 만약에 맞았을 경우, 결과값을 hit_record에 저장해주는 함수
t_bool	hit_record_init_sphere(t_hit_record *rec, t_ray *r, float temp, float radius)
{
	rec->t = temp;
	ray_at(r, rec->t, &(rec->p));
	vec_init(&(rec->normal), rec->p.x, rec->p.y, rec->p.z);
	vec_vec_sub(&rec->normal, r->origin);
	vec_div(&rec->normal, radius);
	return (TRUE);
}

//구에 맞는지 판별하는 함수 - 정리필요
//oc  init 애매함...
t_bool		hit_sphere(t_ray *r, t_hit_record *rec, t_sphere *sphere)
{
	t_vec	oc =  {r->origin->x, r->origin->y, r->origin->z};
	float	a;
	float	b; // half_b in 2*b*b - 4a*c -> so discriminant is b*b - a*c
	float	c;
	float	discriminant;
	float	temp;
	float	radius;

	radius = (float)sphere->dia;
	vec_vec_sub(&oc, &sphere->point);
	a = vec_dot(r->direction, r->direction);
	b = vec_dot(&oc, r->direction);
	c = vec_dot(&oc, &oc) - radius * radius;
	discriminant = b * b - a * c;
	// if (discriminant + 0.005 < 0 || discriminant - 0.005< 0)
	// 	return (FALSE);
	temp = (- b - sqrt(discriminant)) / a;
	if (r->t_min < temp && temp < r->t_max)
		return (hit_record_init_sphere(rec, r, temp, radius));
	// temp = (- b + sqrt(discriminant)) / a;
	// if (temp > r->t_min && temp < r->t_max)
	// 	return (hit_record_init_sphere(rec, r, temp, radius));
	return (FALSE);
}
