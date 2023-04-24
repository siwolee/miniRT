/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:35:50 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/24 21:19:22 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "type.h"

void	*vec_vec_add(void *u, void *v);
void	*vec_vec_mul(void *u, void *v);
void	*vec_vec_sub(void *u, void *v);
void	*vec_vec_div(void *u, void *v);

void	*vec_mul(void *u, double b);
void	*vec_div(void *u, double b);
void	*vec_sub(void *u, double b);
void	*vec_add(void *u, double b);

void	*vec_vec_add_new(void *u, void *v);
void	*vec_vec_mul_new(void *u, void *v);
void	*vec_vec_sub_new(void *u, void *v);
void	*vec_vec_div_new(void *u, void *v);

void	*vec_mul_new(void *u, double b);
void	*vec_div_new(void *u, double b);
void	*vec_sub_new(void *u, double b);
void	*vec_add_new(void *u, double b);

void	vec_init(void *v, double a, double b, double c);
void	*vec_init_new(double a, double b, double c);

double	vec_length_squared(void *a);
double	vec_dot(void *a, void *b);
void	*vec_cross(void *a, void *b);
void	vec_print(void *a);
int		pixel_color_xyz(double x, double y, double z);
int		pixel_color(void *a);

void	*vec_unit_vector(void *a);


#endif