/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:04:35 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/24 17:15:09 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec_init(void *v, double a, double b, double c)
{	
	t_vec	*vec;

	vec = (t_vec *)v;
	vec->x = a;
	vec->y = b;
	vec->z = c;
}

void	*vec_init_new(double a, double b, double c)
{	
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	vec->x = a;
	vec->y = b;
	vec->z = c;
	return ((void *)vec);
}

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

void	*vec_vec_min(void *u, void *v)
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

void	*vec_mul(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x *= b;
	a->y *= b;
	a->z *= b;
	return (a);
}

void	*vec_div(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x /= b;
	a->y /= b;
	a->z /= b;
	return (a);
}

void	*vec_min(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x -= b;
	a->y -= b;
	a->z -= b;
	return (a);
}

void	*vec_add(void *u, double b)
{
	t_vec	*a;

	a = (t_vec *)u;
	a->x += b;
	a->y += b;
	a->z += b;
	return (a);
}


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

void	*vec_vec_min_new(void *u, void *v)
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

void	*vec_min_new(void *u, double b)
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

double vec_dot(void *a, void *b)
{
	t_vec	*u;
	t_vec	*v;

	u = (t_vec *)a;
	v = (t_vec *)b;
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

double vec_length_squared(void *u)
{
	t_vec	*v;

	v = (t_vec *)u;
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

double	vec_length(void *a)
{
	t_vec	*v;

	v = (t_vec *)a;
	return (sqrt(vec_length_squared(v)));
}

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

void	vec_print(void *a)
{
	t_vec	*v;

	v = (t_vec *)a;
	printf("x: %f ", v->x);
	printf("y: %f ", v->y);
	printf("z: %f\n", v->z);
}

int	pixel_color_xyz(double x, double y, double z)
{
	int ir = 255.999 * x;
	int ig = 255.999 * y;
	int ib = 255.999 * z;

	return (ir * 256 * 256 + ig * 256 + ib);
}

int	pixel_color(void *a)
{
	t_vec	*v;

	v = (t_vec *)a;
	int ir = 255.999 * v->x;
	int ig = 255.999 * v->y;
	int ib = 255.999 * v->z;

	return (ir * 256 * 256 + ig * 256 + ib);
}
