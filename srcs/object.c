/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:10:22 by juhyulee          #+#    #+#             */
/*   Updated: 2023/07/07 17:37:08 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// check if the light hits obj
// if hit, hit_result become true
// if hit, hit_record rec is renewed
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
	t_bool	hit_result;

	hit_result = FALSE;
	if (world->type == SP)
		hit_result = hit_sphere(world, ray, rec);
	else if (world->type == PL)
		hit_result = hit_plane(world, ray, rec);
	else if (world->type == CY)
		hit_result = hit_cylinder(world, ray, rec);
	return (hit_result);
}

// add object into world
t_object	*object(t_object_type type, void *element, t_color albedo)
{
	t_object	*new;

	new = (t_object *)malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	new->element = element;
	new->albedo = albedo;
	new->next = NULL;
	return (new);
}

// add object at the last of the list
void	oadd(t_object **list, t_object *new)
{
	t_object	*cur;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

// get the last object
t_object	*olast(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
