/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:00:01 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/23 16:01:46 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_ray 
{
	t_point	*origin;
	t_vec	*direction;
}	t_ray;

void 	ray_init_vec(t_ray *r, void *origin, void *direction);
void 	ray_init_zero(t_ray *r);
void	*ray_at(t_ray *ray, double t);


#endif