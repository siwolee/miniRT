/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:14:14 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/19 21:11:38 by siwolee          ###   ########.fr       */
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

//focal length 적용 안되고 있음
//
// t_camera	camera(t_canvas *canvas, t_point orig, int fov)
// {
// 	t_camera	cam;
// 	double		viewport_height;

// 	viewport_height = 2.0;
// 	// focal_len = 1.0; 
// 	cam.focal_len = (float)canvas->width / 2 / tan(fov / 2);
// 	printf("%0.2f is focal length\n", cam.focal_len);
// 	cam.orig = orig;
// 	// cam.viewport_h = viewport_height;
// 	cam.viewport_h = 
// 	cam.viewport_w = viewport_height * canvas->aspect_ratio;
// 	cam.horizontal = vec(cam.viewport_w, 0, 0);
// 	cam.vertical = vec(0, cam.viewport_h, 0);
// 	cam.left_bottom = vsub(vsub(vsub(cam.orig, vdivn(cam.horizontal, 2))\
// 	, vdivn(cam.vertical, 2)), vec(0, 0, cam.focal_len));

// 	return (cam);
// }

//horizontal vertical이 좀  이이상상하하다다
t_camera camera(t_point lookfrom, t_vec lookat, t_vec vup, double fov, double aspect)
{
	t_camera cam;
	float theta;
	float half_height;
	float half_width;
	t_vec w, u, v;
	
	theta = fov * M_PI / 180;
	printf("aspect %0.2f\n", aspect);
	half_height = tan(theta / 2);
	half_width = aspect * half_height;
	cam.viewport_h = half_height * 2;
	cam.viewport_w = half_width * 2;
	printf("viewport %0.2f %0.2f \n", cam.viewport_h, cam.viewport_w);
	cam.orig = lookfrom;
	w = vunit(vsub(lookfrom, lookat));
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	// lower_left_corner = vec(cam.viewport_w / 2, cam.viewport_h / 2, -1.0);
	cam.focal_len = 1.0;
	cam.left_bottom = vsub(vsub(vsub(cam.orig, vmuln(u, half_width))\
	, vmuln(v, half_height)), w);
	cam.horizontal = vmuln(u, half_width * 2);
	cam.vertical = vmuln(u, half_height * 2);
	return (cam);
}


// t_camera camera(t_point lookfrom, t_vec lookat, t_vec vup, double fov, double aspect)
// {
// 	t_camera cam;
// 	float theta;
// 	float half_height;
// 	float half_width;
// 	t_vec w, u, v;
	
// 	theta = fov * M_PI / 180;
// 	half_height = tan(theta / 2);
// 	half_width = aspect * half_height;
// 	cam.viewport_h = half_height * 2;
// 	cam.viewport_w = half_width * 2;
// 	cam.orig = lookfrom;
// 	w = vunit(vsub(lookfrom, lookat));
// 	u = vunit(vcross(vup, w));
// 	v = vcross(w, u);
// 	// lower_left_corner = vec(cam.viewport_w / 2, cam.viewport_h / 2, -1.0);
// 	cam.focal_len = 1.0;
// 	cam.left_bottom = vsub(vsub(vsub(cam.orig, vmuln(u, half_width))\
// 	, vmuln(v, half_height)), w);
// 	cam.horizontal = vmuln(u, half_width * 2);
// 	cam.vertical = vmuln(u, half_height * 2);
// 	return (cam);
// }
