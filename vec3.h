/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:35:50 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/21 19:53:40 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct s_mlx
{
	void *mlx;
	void *win; 
	void *img;
	int	*data;
	int bpp;
	int size_l;
	int endian;
	int color[3];
}t_mlx;

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

t_vec *vec_vec_add(void *u, void *v);
t_vec *vec_vec_mul(void *u, void *v);
t_vec *vec_vec_min(void *u, void *v);
t_vec *vec_vec_div(void *u, void *v);

t_vec *vec_mul(void *u, int b);
t_vec *vec_div(void *u, int b);
t_vec *vec_min(void *u, int b);
t_vec *vec_add(void *u, int b);

t_vec *vec_vec_add_new(void *u, void *v);
t_vec *vec_vec_mul_new(void *u, void *v);
t_vec *vec_vec_min_new(void *u, void *v);
t_vec *vec_vec_div_new(void *u, void *v);

t_vec *vec_mul_new(void *u, int b);
t_vec *vec_div_new(void *u, int b);
t_vec *vec_min_new(void *u, int b);
t_vec *vec_add_new(void *u, int b);

void	vec_init(void *v, double a, double b, double c);
void	*vec_init_new(double a, double b, double c);

double	vec_length_squared(void *a);
double	vec_dot(void *a, void *b);
t_vec	*vec_cross(void *a, void *b);
void	vec_print(void *a);
int		pixel_color_xyz(double x, double y, double z);
int		pixel_color(void *a);

t_vec	*vec_unit_vector(void *a);


#endif