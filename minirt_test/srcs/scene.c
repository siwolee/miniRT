/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:51:55 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 15:32:55 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_scene	*scene_init(void)
{
	t_scene		*scene;
	t_object	*world;
	t_object	*lights;
	double		ka;

	if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	scene->camera = camera(v_create(0,0,0), v_create(0,0,0));
	world = object(SP, sphere(v_create(-2, 0, -5), 2), v_create(0.5, 0, 0)); // world 에 구1 추가
    oadd(&world, object(SP, sphere(v_create(2, 0, -5), 2), v_create(0, 0.5, 0))); // world 에 구2 추가
    oadd(&world, object(SP, sphere(v_create(0, -1000, 0), 995), v_create(1, 1, 1)));
	lights = object(LIGHT_POINT, light_point(v_create(0, 20, 0), v_create(1, 1, 1), 0.5), v_create(0, 0, 0));
	scene->world = world;
	lights = object(LIGHT_POINT, light_point(v_create(0, 5, 0), v_create(1, 1, 1), 0.5), v_create(0,0,0));
	scene->light = lights;
	ka = 0.1;
	scene->ambient = v_mul_n(v_create(1, 1, 1), ka);
	return (scene);
}

t_hit_record record_init(void)
{
	t_hit_record	record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}
