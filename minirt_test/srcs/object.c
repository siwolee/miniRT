/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 22:59:04 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 14:46:47 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*object(t_object_type type, void *element, t_color albedo)
{
	t_object	*new;

	if (!(new = (t_object *)malloc(sizeof(t_object))))
		return (0);
	new->type = type;
	new->element = element;
	new->next = NULL;
	new->albedo = albedo;
	return (new);
}

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

t_object	*olast(t_object *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
