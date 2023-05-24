/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:14:14 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/24 15:54:30 by siwolee          ###   ########.fr       */
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

t_camera *camera(t_point lookfrom, t_vec lookat, double fov, double aspect)
{
	t_camera	*cam;
	float		theta;
	t_vec		w;
	t_vec		u;
	t_vec		v;
	
	cam = malloc(sizeof(t_camera));
	if (!cam)
		exit_error(5);
	cam->fov = fov;
	cam->dir = lookat;
	cam->aspect = aspect;
	cam->vup = vec(0, 1, 0);
	theta = fov * M_PI / 180;
	cam->viewport_h = (tan(theta / 2)) * 2;
	cam->focal_len = 1 / tan(fov / 2);
	printf("focal len %f\n", cam->focal_len);
	cam->viewport_w = aspect * cam->viewport_h;
	cam->orig = lookfrom;
	w = vunit(vsub(lookfrom, lookat));
	u = vunit(vcross(cam->vup, w));
	v = vcross(w, u);
	cam->left_bottom = vsub(vsub(vsub(cam->orig, \
	vmuln(u, cam->viewport_w / 2)), vmuln(v, cam->viewport_h / 2)), w);
	cam->horizontal = vmuln(u, cam->viewport_w);
	cam->vertical = vmuln(v, cam->viewport_h);
	return (cam);
}

void	move_camera(t_camera *cam, t_vec vup)
{
	// float		theta;
	t_vec		w;
	t_vec		u;
	t_vec		v;
	
	cam->orig = vup;
	cam->focal_len = 1 / tan(cam->fov / 2);
	w = vunit(vsub(cam->orig, cam->dir));
	u = vunit(vcross(vup, w));
	v = vcross(w, u);
	cam->left_bottom = vsub(vsub(vsub(cam->orig, \
	vmuln(u, cam->viewport_w / 2)), vmuln(v, cam->viewport_h / 2)), w);
	cam->horizontal = vmuln(u, cam->viewport_w);
	cam->vertical = vmuln(v, cam->viewport_h);
}
