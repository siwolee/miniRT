/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:35:50 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/17 16:37:46 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include <math.h>
#include <stdio.h>
typedef struct s_vec
{
	double x;
	double y;
	double z;
}t_vec; 

typedef struct s_point
{
	double x;
	double y;
	double z;
}t_point; 

typedef struct s_color
{
	double r;
	double b;
	double g;
}t_color; 

int	pixel_color(double x, double y, double z);

t_vec *vec_vec_add(t_vec *a, t_vec *b);
t_vec *vec_vec_mul(t_vec *a, t_vec *b);
t_vec *vec_vec_min(t_vec *a, t_vec *b);
t_vec *vec_vec_div(t_vec *a, t_vec *b);

t_vec *vec_mul(t_vec *a, int b);
t_vec *vec_div(t_vec *a, int b);
t_vec *vec_min(t_vec *a, int b);
t_vec *vec_add(t_vec *a, int b);

t_vec *vec_vec_add_new(t_vec *a, t_vec *b);
t_vec *vec_vec_mul_new(t_vec *a, t_vec *b);
t_vec *vec_vec_min_new(t_vec *a, t_vec *b);
t_vec *vec_vec_div_new(t_vec *a, t_vec *b);

t_vec *vec_mul_new(t_vec *a, int b);
t_vec *vec_div_new(t_vec *a, int b);
t_vec *vec_min_new(t_vec *a, int b);
t_vec *vec_add_new(t_vec *a, int b);

void	vec_init(t_vec *vec, int a, int b, int c);
double vec_length_squared(t_vec *v);
double vec_dot(t_vec *u, t_vec *v);
t_vec *vec_cross(t_vec *u, t_vec *v);
void	vec_print(t_vec *v);
int	pixel_color(double x, double y, double z);


#endif