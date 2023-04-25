/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitable.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:34:51 by siwolee           #+#    #+#             */
/*   Updated: 2023/04/25 16:04:58 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HITABLE_H
# define HITABLE_H

# include "ray.h"
# include "vec3.h"
# include "type.h"

/*
	아직 뭐가뭔지 모름
*/
typedef struct s_hit_record
{
	float	t;
	t_vec	p;
	t_vec	normal;
}	t_hit_record;


//물체들을 통합해서 가지고 있는 리스트.
//data는 각 물체의 포인터를 가지고
//type은 무슨 물체인지 알려줌
typedef struct s_hitable
{
	void			*data;
	int 			type;
	struct s_list	*next;
	struct s_list	*prev;

}	t_hitable;

//물체들을 돌면서 맞았는지 아닌지 판별하는 함수. 결과값은 rec에 저장
t_bool	hit(t_hitable *node, const t_ray *r, t_hit_record *rec);

//hit record 복사 함수 
void	hit_record_dup(t_hit_record *temp, t_hit_record *rec);

// type별로 광선 맞았는지 아닌지 판별하게 분류하는 함수. 리턴값은 동일하게 t_bool
t_bool	hit_whatever(t_hitable *node, t_hit_record *rec, t_ray *r, float t_min, float t_max);

// 구에서 만약에 맞았을 경우, 결과값을 hit_record에 저장해주는 함수
t_bool	hit_record_init_sphere(t_hit_record *rec, t_ray *r, float temp, float radius);

//구에 맞는지 판별하는 함수 - 정리필요
t_bool	hit_sphere(const t_ray *r, t_hit_record *rec, t_sphere *sphere);


#endif