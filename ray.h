/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:00:01 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/17 13:04:11 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_ray 
{
	t_point	*origin;
	t_point	*direction;
}	t_ray;


t_vec	*ray_at(t_ray *ray, double t);

#endif