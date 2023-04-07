/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:35:50 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/07 16:53:22 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec
{
	double x;
	double y;
	double z;
}t_vec; 

#include <math.h>
#include <stdio.h>

int	pixel_color(double x, double y, double z);




#endif