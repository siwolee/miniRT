/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 13:00:01 by siwolee           #+#    #+#             */
/*   Updated: 2023/05/01 21:28:16 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "type.h"

# define T_MIN (-1.0)
# define T_MAX (1.0)

// t_min및 t_max는 -1 ~ 1 사이에 있다고 가정.
// rgb값으로 변환시에 필요..
typedef struct s_ray
{
	t_point	origin;
	t_vec	direction;
	float	t_min;
	float	t_max;
}	t_ray;

//초기화 - 기존 포인터를 넣어주기, minmax는 기본값
void 	ray_init_vec(t_ray *r, void *origin, void *direction);

//초기화 - origin, direction에 0.0.0으로 새로 할당한 포인터 넣기
//minmax는 역시 기본값
void 	ray_init_zero(t_ray *r);

//ray의 origin부터 direction까지, t배의 거리를 갔을 때의 좌표 리턴
//t가 1일 경우에는 direction 리턴
void	*ray_at_new(t_ray *ray, double t);
void	ray_at(t_ray *ray, double t, void *new);

#endif
