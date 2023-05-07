/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:16:33 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 15:20:16 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_vec	v_sub(t_vec u, t_vec v)
{//두 벡터 요소끼리 뺌
	t_vec	vec;

	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

t_vec	v_div(t_vec u, double t)
{//벡터 요소들을 스칼라 t로 나눔
	t_vec	vec;

	vec.x = u.x / t;
	vec.y = u.y / t;
	vec.z = u.z / t;
	return (vec);
}

double	length_squared(t_vec u)
{//벡터의 길이 제곱한거
	return (u.x * u.x + u.y * u.y + u.z * u.z);
}

double	length(t_vec u)
{//벡터의 길이
	return (sqrt(length_squared(u)));
}

t_vec	unit_vecter(t_vec u)
{//단위 벡터 구함
	double len;

	len = length(u);
	if (len == 0)
		exit(0);
	return (v_div(u, length(u)));
}

t_vec	at(t_ray r, double t)
{
	return (v_add(r.origin, v_mul_n(r.direction, t)));
}

t_vec	v_cross(t_vec v1, t_vec v2)
{//벡터 외적
	t_vec	out;

	out.x = v1.y * v2.z + v1.z * v2.y;
	out.y = v1.z * v2.x + v1.x * v2.z;
	out.z = v1.x * v2.y + v1.y * v2.x;

	return (out);
}

void	print_vec(t_vec v)
{
	printf("%lf %lf %lf\n", v.x, v.y, v.z);
}

// 두 벡터의 원소를 비교하여 작은 값들만 반환
t_vec  v_min(t_vec vec1, t_vec vec2)
{
    if (vec1.x > vec2.x)
        vec1.x = vec2.x;
    if (vec1.y > vec2.y)
        vec1.y = vec2.y;
    if (vec1.z > vec2.z)
        vec1.z = vec2.z;
    return (vec1);
}

t_vec      v_mul_v(t_vec vec, t_vec vec2)
{
    vec.x *= vec2.x;
    vec.y *= vec2.y;
    vec.z *= vec2.z;
    return (vec);
}

t_vec	reflect(t_vec v, t_vec n)
{
	return (v_sub(v, v_mul_n(n, dot(v, n) * 2)));
}
