/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 19:42:51 by siwolee           #+#    #+#             */
/*   Updated: 2023/06/01 19:49:03 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

void	*free_cam(t_camera *node)
{
	t_camera	*next;

	if (!node)
		return (NULL);
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	return (NULL);
}

void	*free_object(t_object *node)
{
	t_object	*next;

	if (!node)
		return (NULL);
	while (node)
	{
		next = node->next;
		free(node->element);
		free(node);
		node = next;
	}
	return (NULL);
}

// camera, world, light
void	free_vars(t_vars *vars)
{
	vars->scene.camera = free_cam(vars->scene.camera);
	vars->scene.world = free_object(vars->scene.world);
	vars->scene.light = free_object(vars->scene.light);
}
