/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:14:14 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 18:24:03 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_canvas	canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_camera	camera(t_canvas *canvas, t_point orig)
{
	t_camera	cam;
	double		focal_len;
	double		viewport_height;

	viewport_height = 2.0;
	focal_len = 1.0;//cam.focal_len = (float)WIDTH / 2 / get_tan(cam.fov / 2);
	cam.orig = orig;
	cam.viewport_h = viewport_height;
	cam.viewport_w = viewport_height * canvas->aspect_ratio;
	cam.focal_len = focal_len;
	cam.horizontal = vec(cam.viewport_w, 0, 0);
	cam.vertical = vec(0, cam.viewport_h, 0);
	cam.left_bottom = vsub(vsub(vsub(cam.orig, vdivn(cam.horizontal, 2))\
	, vdivn(cam.vertical, 2)), vec(0, 0, focal_len));

	return (cam);
}
