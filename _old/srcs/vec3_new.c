/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:16:33 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/10 16:05:59 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"
#include "ray.h"

t_vec	v_create(double x, double y, double z)
{//벡터 구조체 생성
	t_vec	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec	v_add(t_vec u, t_vec v)
{//두 벡터 요소끼리 더함
	t_vec	vec;

	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	vec.z = u.z + v.z;
	return (vec);
}

t_vec	v_mul(t_vec u, t_vec v)
{//벡터 요소끼리 곱
	t_vec	vec;

	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	vec.z = u.z * v.z;
	return (vec);
}

t_vec	v_mul_n(t_vec u, double t)
{//벡터에 스칼라 n을 곱해서 리턴
	t_vec	vec;

	vec.x = u.x * t;
	vec.y = u.y * t;
	vec.z = u.z * t;
	return (vec);
}

double	dot(t_vec u, t_vec v)
{//벡터 내적
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}


t_vec	v_subv(t_vec u, t_vec v)
{//두 벡터 요소끼리 뺌
	t_vec	vec;

	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

//벡터 요소들을 스칼라 n로 나눔
t_vec	v_divn(t_vec u, double t)
{
	t_vec	vec;

	vec.x = u.x / t;
	vec.y = u.y / t;
	vec.z = u.z / t;
	return (vec);
}

//벡터의 길이 제곱한거
double	length_squared(t_vec u)
{
	return (u.x * u.x + u.y * u.y + u.z * u.z);
}

//벡터의 길이
double	length(t_vec u)
{
	return (sqrt(length_squared(u)));
}

//단위 벡터 구함
t_vec	unit_vecter(t_vec u)
{
	return (v_div(u, length(u)));
}

t_vec	at(t_ray r, double t)
{
	return (v_add(r.origin, v_mul_n(r.direction, t)));
}

//벡터 외적
t_vec	vec_cross(t_vec *v1, t_vec *v2)
{
	t_vec	out;

	out.x = v1->y * v2->z + v1->z * v2->y;
	out.y = v1->z * v2->x + v1->x * v2->z;
	out.z = v1->x * v2->y + v1->y * v2->x;

	return (out);
}
