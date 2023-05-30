/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:14:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/27 22:14:29 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_face_normal(t_ray *r, t_hit_record *rec)
{
	if (vdot(r->dir, rec->normal) < 0)
	{
		rec->front_face = TRUE;
		rec->normal = rec->normal;
	}
	else
	{
		rec->front_face = FALSE;
		rec->normal = vmuln(rec->normal, -1);
	}
}
