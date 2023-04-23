/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:00:01 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/23 11:55:34 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_ray 
{
	t_point	*origin;
	t_point	*direction;
}	t_ray;

void 	*ray_init_vec(t_ray *r, void *origin, void *direction);
void 	*ray_init_zero(t_ray *r);
t_vec	*ray_at(t_ray *ray, double t);
void 	*ray_init_zero(t_ray *r);
void 	*ray_init_vec(t_ray *r, void *origin, void *direction);


#endif