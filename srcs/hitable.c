/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:42:44 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/28 21:21:31 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hitable.h"
#include "vec3.h"

//물체들을 돌면서 맞았는지 아닌지 판별하는 함수. 결과값은 rec에 저장
t_bool	hit(t_hitable *node, t_ray *r, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	t_bool			hit_anything = FALSE;
	double			closest_so_far = 0;
	int				i;

	i = 0;
	while (node)
	{
		// 순서대로 넣기 때문에 아직 비교는 안하고 있음
		if (hit_whatever(node, &temp_rec, r) == TRUE)
		{
			hit_anything = TRUE;
			if (closest_so_far != 0)
				printf("t is %f\n", temp_rec.t);
			closest_so_far = temp_rec.t;
			hit_record_dup(&temp_rec, rec);
		}
		node = node->next;
		i++;
		// printf("%d\n", i);
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

int	cy_boundary(t_cylinder *cy, t_vec at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vdot(vminus(at_point, cy->point), cy->vec);
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (0);
	return (1);
}

t_vec	*get_cylinder_normal(t_cylinder *cy, t_vec at_point, double hit_height)
{
    t_vec	*hit_center;
    t_vec	 *normal;

    hit_center = vec_vec_add(&(cy->point), vec_mul(&(cy->vec), hit_height));
    normal = vec_vec_sub(&at_point, &hit_center);

    return (vec_unit_vector(normal));
}

t_bool	hit_cylinder(t_ray *r, t_hit_record *rec, t_cylinder *cylinder)
{
	double	a; // u,o를 외적한 벡터의 제곱
	double	half_b; // u,o 의 외적한 벡터와 p와 o의 외적한 벡터를 내적
	double	c;
	t_vec	*u; // 광선의 방향 벡터
	t_vec	*o; // 원기둥의 방향 벡터
	t_vec	*p; // 광선의 원점 - 원기둥의 중심점
	double	rad; // 원기둥의 반지름

	double	discriminant; // 판별식
	double	sqrtd;
	double	root;
	double	hit_height;

	u = r->direction;
	o = &(cylinder->vec);
	rad = ((cylinder->dia) / 2);
	p = (t_vec *)vec_vec_sub(r->origin, &(cylinder->point));
	a = vec_length(vec_cross(u, o));
	half_b = vec_dot(vec_cross(u, o), vec_cross(p, o));
	c = vec_length(vec_cross(p, o)) - pow(rad, 2);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < r->t_min || r->t_max < root)
	{
		root = (-half_b + sqrtd) / a;
			if (root < r->t_min || r->t_max < root)
				return (FALSE);
	}
	if (!(hit_height = cy_boundary(cylinder, ray_at(r, root))))
		return (FALSE);
	rec->t = root; // 광선의 원점과 교점까지의 거리
	rec->p = ray_at(r, root); //교점의 좌표
	rec->normal = get_cylinder_normal(cylinder, rec->p, hit_height);
	set_face_normal(r, rec);
	return (TRUE);
}

// int	hit_cylinder_cap(t_ray *ray, t_hit_record *rec, double height, t_cylinder *cy)
// {
// 	double	rad = cy->dia / 2;
// 	t_vec	circle_center = vec_add(cy->point, vec_mul(cy->dia, height));
// 	float	root = vec_dot(vec_sub(circle_center, ray->origin), cy->dir) \
// 	/ vec_dot(ray->direction, cy->vec);
// 	float	diameter = vec_length(vec_sub(circle_center, ray_at(ray, root)));
// 	if (fabs(r) < fabs(diameter))
// 		return (0);
// 	if (root < ray->t_min || ray->t_max < root)
// 		return (0);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	return (1);
// }
// t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
// {
//     const t_cylinder *cy = cy_obj->element;
//     int result;

//     result = 0;
//     result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
//     result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
//     result += hit_cylinder_side(cy_obj, ray, rec);
//     return (result);
// }
