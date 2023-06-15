/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:14:14 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/15 15:18:54 by siwolee          ###   ########.fr       */
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

//right (or left) is perpendicular to forward and parrel to the floor(x, 0, z) 
// = it's cross to the (forward, normalized y-axis(0, 1, 0))
//then vup = cross(forward, right);
void	camera_sub(t_camera *cam, float theta, double fov, double aspect, t_vec forward)
{
	t_vec	right;

	cam->fov = fov;
	cam->aspect = aspect;
	right = vcross(forward, vec(0, -1, 0));
	cam->vup = vcross(forward, right);
	cam->viewport_h = (tan(theta / 2)) * 2;
	cam->focal_len = 1 / tan(fov / 2);
	cam->viewport_w = aspect * cam->viewport_h;
	cam->theta = theta;
}

t_camera	*camera(t_point lookfrom, t_vec lookat, double fov, double aspect)
{
	t_camera	*cam;
	float		theta;
	t_vec		forward;
	t_vec		u;
	t_vec		v;

	cam = malloc(sizeof(t_camera));
	if (!cam)
		exit_error(ERROR_NO_CAMERA);
	theta = fov * M_PI / 180;
	forward = vunit(vsub(lookfrom, lookat));
	camera_sub(cam, theta, fov, aspect, forward);
	cam->orig = lookfrom;
	cam->dir = lookat;
	u = vunit(vcross(cam->vup, forward));
	v = vcross(forward, u);
	cam->left_bottom = vsub(vsub(vsub(cam->orig, \
	vmuln(u, cam->viewport_w / 2)), vmuln(v, cam->viewport_h / 2)), forward);
	cam->horizontal = vmuln(u, cam->viewport_w);
	cam->vertical = vmuln(v, cam->viewport_h);
	cam->next = NULL;
	cam->num = 0;
	return (cam);
}

void	move_camera(t_camera *cam)
{
	t_vec		forward;
	t_vec		u;
	t_vec		v;

	cam->focal_len = 1 / tan(cam->fov / 2);
	forward = vunit(vsub(cam->orig, cam->dir));
	u = vunit(vcross(cam->vup, forward));
	v = vcross(forward, u);
	cam->left_bottom = vsub(vsub(vsub(cam->orig, \
	vmuln(u, cam->viewport_w / 2)), vmuln(v, cam->viewport_h / 2)), forward);
	cam->horizontal = vmuln(u, cam->viewport_w);
	cam->vertical = vmuln(v, cam->viewport_h);
}
