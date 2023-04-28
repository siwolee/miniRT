/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:04:35 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/28 20:33:26 by juhyulee         ###   ########.fr       */
=======
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:04:35 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/28 21:12:57 by siwolee          ###   ########.fr       */
>>>>>>> 86bb8ae5666f1fed89cfd270da31a23a37bb95d8
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// 한번에 값을 넣어줘용
void	vec_init(void *v, double a, double b, double c)
{
	t_vec	*vec;

	vec = (t_vec *)v;
	vec->x = a;
	vec->y = b;
	vec->z = c;
}

//한번에 값을 넣어줘용 + 동적할당
void	*vec_init_new(double a, double b, double c)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	vec->x = a;
	vec->y = b;
	vec->z = c;
	return ((void *)vec);
}

//앞쪽 벡터에 뒤쪽 벡터를 더해용
void	*vec_vec_add(void *u, void *v)
{
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	return (a);
}

//앞쪽 벡터에 뒤쪽 벡터를 곱함
void	*vec_vec_mul(void *u, void *v)
{
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	a->x *= b->x;
	a->y *= b->y;
	a->z *= b->z;
	return (a);
}

//앞쪽 벡터에 뒤쪽 벡터를 뺌
void	*vec_vec_sub(void *u, void *v)
{
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	return (a);
}

////앞쪽 벡터에 뒤쪽 벡터를 나눔
void	*vec_vec_div(void *u, void *v)
{
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	a->x /= b->x;
	a->y /= b->y;
	a->z /= b->z;
	return (a);
}


////앞쪽 벡터를 뒤쪽 수로 곱함
void	*vec_mul(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x *= b;
	a->y *= b;
	a->z *= b;
	return (a);
}

////앞쪽 벡터를 뒤쪽 수로 나눔
void	*vec_div(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x /= b;
	a->y /= b;
	a->z /= b;
	return (a);
}

////앞쪽 벡터를 뒤쪽 수로 뺌
void	*vec_sub(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x -= b;
	a->y -= b;
	a->z -= b;
	return (a);
}


////앞쪽 벡터를 뒤쪽 수로 더함
void	*vec_add(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x += b;
	a->y += b;
	a->z += b;
	return (a);
}


//앞쪽 벡터에 뒤쪽 벡터를 더해용 + 동적할당
void	*vec_vec_add_new(void *u, void *v)
{
	t_vec *temp;
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x += b->x;
	temp->y += b->y;
	temp->z += b->z;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 벡터를 곱함 + 동적할당
void	*vec_vec_mul_new(void *u, void *v)
{
	t_vec *temp;
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x *= b->x;
	temp->y *= b->y;
	temp->z *= b->z;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 벡터를 뺌 + 동적할당
void	*vec_vec_sub_new(void *u, void *v)
{
	t_vec *temp;
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x = a->x - b->x;
	temp->y = a->y - b->y;
	temp->z = a->z - b->z;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 벡터를 나눔 + 동적할당
void	*vec_vec_div_new(void *u, void *v)
{
	t_vec *temp;
	t_vec	*a;
	t_vec	*b;

	a = (t_vec *)u;
	b = (t_vec *)v;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x /= b->x;
	temp->y /= b->y;
	temp->z /= b->z;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 수를 곱함 + 동적할당
void	*vec_mul_new(void *u, double b)
{
	t_vec *temp;
	t_vec	*a;

	a = (t_vec *)u;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x *= b;
	temp->y *= b;
	temp->z *= b;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 수를 나눔 + 동적할당
void	*vec_div_new(void *u, double b)
{
	t_vec *temp;
	t_vec	*a;

	a = (t_vec *)u;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x /= b;
	temp->y /= b;
	temp->z /= b;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 수를 뺌 + 동적할당
void	*vec_sub_new(void *u, double b)
{
	t_vec *temp;
	t_vec	*a;

	a = (t_vec *)u;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x -= b;
	temp->y -= b;
	temp->z -= b;
	return (temp);
}

//앞쪽 벡터에 뒤쪽 수를 더함 + 동적할당
void	*vec_add_new(void *u, double b)
{
	t_vec *temp;
	t_vec	*a;

	a = (t_vec *)u;
	temp = malloc(sizeof(t_vec));
	vec_init(temp, a->x, a->y, a->z);
	temp->x += b;
	temp->y += b;
	temp->z += b;
	return (temp);
}

//벡터 벡터 내적
double vec_dot(void *a, void *b)
{
	t_vec	*u;
	t_vec	*v;

	u = (t_vec *)a;
	v = (t_vec *)b;
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

double vec_power(void *u)
{
	t_vec	*v;

	v = (t_vec *)u;
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

//vec_power의 제곱근
double	vec_length(void *a)
{
	t_vec	*v;

	v = (t_vec *)a;
	return (sqrt(vec_power(v)));
}

//이건사실나도몰루 하래서 함...
void	*vec_unit_vector(void *a)
{
	t_vec	*v;
	t_vec	*temp;
	double	length;

	v = (t_vec *)a;
	length = vec_length(v);
	temp = vec_div(v, length);
	return (temp);
}

//위에다가 동적할당
void	*vec_unit_vector_new(void *a)
{
	t_vec	*v;
	t_vec	*temp;
	double	length;

	v = (t_vec *)a;
	length = vec_length(v);
	temp = vec_div_new(v, length);
	return (temp);
}

//벡터벡터간 교차점 구하기
void	*vec_cross(void *a, void *b)
{
	t_vec	*temp;
	t_vec	*u;
	t_vec	*v;

	u = (t_vec *)a;
	v = (t_vec *)b;
	temp = malloc(sizeof(t_vec));
	if (!temp)
		return (0);
	temp->x = (u->y * v->z) - (u->z * v->y);
	temp->y = (u->z * v->x) - (u->x * v->z);
	temp->z = (u->x * v->y) - (u->y * v->x);
	return (temp);
}

//프린트 세개 해준다
void	vec_print(void *a)
{
	t_vec	*v;

	v = (t_vec *)a;
	printf("x: %f ", v->x);
	printf("y: %f ", v->y);
	printf("z: %f\n", v->z);
}

//0 - 1 사이의 컬러값을 합해서 mlx에 넣는 int 값으로 바꿔줌
int	pixel_color_xyz(double x, double y, double z)
{
	int ir = 255.999 * x;
	int ig = 255.999 * y;
	int ib = 255.999 * z;

	return (ir * 256 * 256 + ig * 256 + ib);
}

//벡터 가지고 0 - 1 사이의 컬러값을 합해서 mlx에 넣는 int 값으로 바꿔줌
int	pixel_color(void *a)
{
	t_vec	*v;

	v = (t_vec *)a;
	int ir = 255.999 * v->x;
	int ig = 255.999 * v->y;
	int ib = 255.999 * v->z;

	return (ir * 256 * 256 + ig * 256 + ib);
}
