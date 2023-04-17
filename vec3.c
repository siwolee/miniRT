/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:04:35 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/17 16:36:58 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

void	vec_init(t_vec *vec, int a, int b, int c)
{
	vec->x = a;
	vec->y = b;
	vec->z = c;
}

t_vec *vec_vec_add(t_vec *a, t_vec *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	return (a);
}

t_vec *vec_vec_mul(t_vec *a, t_vec *b)
{
	a->x *= b->x;
	a->y *= b->y;
	a->z *= b->z;
	return (a);
}

t_vec *vec_vec_min(t_vec *a, t_vec *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	return (a);
}

t_vec *vec_vec_div(t_vec *a, t_vec *b)
{
	a->x /= b->x;
	a->y /= b->y;
	a->z /= b->z;
	return (a);
}

t_vec *vec_mul(t_vec *a, int b)
{
	a->x *= b;
	a->y *= b;
	a->z *= b;
	return (a);
}

t_vec *vec_div(t_vec *a, int b)
{
	a->x /= b;
	a->y /= b;
	a->z /= b;
	return (a);
}

t_vec *vec_min(t_vec *a, int b)
{
	a->x -= b;
	a->y -= b;
	a->z -= b;
	return (a);
}

t_vec *vec_add(t_vec *a, int b)
{
	a->x += b;
	a->y += b;
	a->z += b;
	return (a);
}


t_vec *vec_vec_add_new(t_vec *a, t_vec *b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x += b->x;
	temp->y += b->y;
	temp->z += b->z;
	return (a);
}

t_vec *vec_vec_mul_new(t_vec *a, t_vec *b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x *= b->x;
	temp->y *= b->y;
	temp->z *= b->z;
	return (a);
}

t_vec *vec_vec_min_new(t_vec *a, t_vec *b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x -= b->x;
	temp->y -= b->y;
	temp->z -= b->z;
	return (a);
}

t_vec *vec_vec_div_new(t_vec *a, t_vec *b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x /= b->x;
	temp->y /= b->y;
	temp->z /= b->z;
	return (a);
}

t_vec *vec_mul_new(t_vec *a, int b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x *= b;
	temp->y *= b;
	temp->z *= b;
	return (a);
}

t_vec *vec_div_new(t_vec *a, int b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x /= b;
	temp->y /= b;
	temp->z /= b;
	return (a);
}

t_vec *vec_min_new(t_vec *a, int b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x -= b;
	temp->y -= b;
	temp->z -= b;
	return (a);
}

t_vec *vec_add_new(t_vec *a, int b)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	init_vec(a->x, a->y, a->z);
	temp->x += b;
	temp->y += b;
	temp->z += b;
	return (a);
}

double vec_length_squared(t_vec *v)
{
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

double vec_dot(t_vec *u, t_vec *v)
{
	return ((u->x * v->x) + (u->y * v->y) + (u->z * v->z));
}

double	vec_length(t_vec *v)
{
	return (sqrt(length_squared(v)));
}

t_vec	*vec_unit_vector(t_vec *v)
{
	return (vec_div(v, vec_length(v)));
}

t_vec *vec_cross(t_vec *u, t_vec *v)
{
	t_vec *temp;

	temp = malloc(sizeof(t_vec));
	if (!temp)
		return (0);
	temp->x = (u->y * v->z) - (u->z * v->y);
	temp->y = (u->z * v->x) - (u->x * v->z);
	temp->z = (u->x * v->y) - (u->y * v->x);
	return (temp);
}

void	vec_print(t_vec *v)
{
	printf("x: %f ", v->x);
	printf("y: %f ", v->y);
	printf("z: %f\n", v->z);
}



# define PIXEL_RGB(x, y, z) (x * 256 * 256 + y * 256 + z)

int	pixel_color(double x, double y, double z)
{
	int ir = 255.999 * x;
	int ig = 255.999 * y;
	int ib = 255.999 * z;

	return (PIXEL_RGB(ir, ig, ib));
}