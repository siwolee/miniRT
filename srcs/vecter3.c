/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecter3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:08:28 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/08 20:06:31 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vmin(t_vec vec1, t_vec vec2)
{
	if (vec1.x > vec2.x)
		vec1.x = vec2.x;
	if (vec1.y > vec2.y)
		vec1.y = vec2.y;
	if (vec1.z > vec2.z)
		vec1.z = vec2.z;
	return (vec1);
}

t_vec	reflect(t_vec v, t_vec n)
{
	return (vsub(v, vmuln(n, vdot(v, n) * 2)));
}

void	print_vec(t_vec t)
{
	printf("x : %lf y : %lf z : %lf\n", t.x, t.y, t.z);
}
