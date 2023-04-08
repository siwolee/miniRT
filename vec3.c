/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:04:35 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/07 16:52:58 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec *vec_add_vec(t_vec *a, t_vec *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	return (a);
}

t_vec *vec_multiply(t_vec *a, int b)
{
	a->x += b;
	a->y += b;
	a->z += b;
	return (a);
}

void	vec_init(t_vec *vec, int a, int b, int c)
{
	vec->x = a;
	vec->y = b;
	vec->z = c;
}

double vec_length_squared(t_vec *v)
{
	return (pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
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