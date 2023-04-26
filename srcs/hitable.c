/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:42:44 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/27 02:00:42 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "vec3.h"

//물체들을 돌면서 맞았는지 아닌지 판별하는 함수. 결과값은 rec에 저장
t_bool	hit(t_hitable *node, t_ray *r, t_hit_record *rec)
{
	// const t_hit_record test = {0, 0, 0};
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
			if (closest_so_far > 1) {
				printf("%f\n", closest_so_far);
				continue ;
			}
			hit_record_dup(&temp_rec, rec);
			// temp_rec = test;
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
	vec_init(&(rec->p), temp->p.x, temp->p.y, temp->p.z);
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
	// printf("%f\n", rec->t);
	ray_at(r, rec->t, &(rec->p));
	// vec_print(&rec->p);
	// rec->normal =(rec->p - r->origin) / radius;
	// printf("aa");
	// vec_print(&(rec->normal));
	vec_init(&(rec->normal), rec->p.x, rec->p.y, rec->p.z);
	// vec_print(&(rec->normal));
	// exit(1);
	// printf("rec->normal: \n");
	// vec_print(&(rec->normal));
	// printf("rec->origin: \n");
	// vec_print(&r->origin);
	// printf("\n");
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

	// printf("%f %f %f\n", sphere->point.x, sphere->point.y, sphere->point.z);
	// radius = (float)(sphere->dia * (0.5));
	radius = 1;
	vec_vec_sub(&oc, &sphere->point);
	// oc = vec_init_new(r->origin->x, r->origin->y, r->origin->z);
	// oc = {r->origin->x, r->origin->y, r->origin->z};
	a = vec_dot(r->direction, r->direction);
	b = vec_dot(&oc, r->direction);
	c = vec_dot(&oc, &oc) - radius * radius;
	discriminant = b * b - a * c;
	if (discriminant + 0.005 < 0 || discriminant - 0.005< 0)
		return (FALSE);
	temp = (- b - sqrt(discriminant)) / a;
	// printf("%f , %f \n", r->t_max, r->t_min);
	if (r->t_min < temp && temp < r->t_max)
		return (hit_record_init_sphere(rec, r, temp, radius));
	// temp = (- b + sqrt(discriminant)) / a;
	// if (temp > r->t_min && temp < r->t_max)
	// 	return (hit_record_init_sphere(rec, r, temp, radius));~
	return (FALSE);
}
