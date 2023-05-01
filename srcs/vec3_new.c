/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:16:33 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/01 21:08:09 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	v_create(double x, double y, double z)
{//벡터 구조체 생성
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	v_add(t_vec3 u, t_vec3 v)
{//두 벡터 요소끼리 더함
	t_vec3	vec;

	vec.x = u.x + v.x;
	vec.y = u.y + v.y;
	vec.z = u.z + v.z;
	return (vec);
}

t_vec3	v_mul(t_vec3 u, t_vec3 v)
{//벡터 요소끼리 곱
	t_vec3	vec;

	vec.x = u.x * v.x;
	vec.y = u.y * v.y;
	vec.z = u.z * v.z;
	return (vec);
}

double	dot(t_vec3 u, t_vec3 v)
{//벡터 내적
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

t_vec3	v_sub(t_vec3 u, t_vec3 v)
{//두 벡터 요소끼리 뺌
	t_vec3	vec;

	vec.x = u.x - v.x;
	vec.y = u.y - v.y;
	vec.z = u.z - v.z;
	return (vec);
}

t_vec3	v_div(t_vec3 u, double t)
{//벡터 요소들을 스칼라 t로 나눔
	t_vec3	vec;

	vec.x = u.x / t;
	vec.y = u.y / t;
	vec.z = u.z / t;
	return (vec);
}
