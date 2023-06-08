/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_tilt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:09:50 by siwolee           #+#    #+#             */
/*   Updated: 2023/06/08 20:26:36 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"


// https://m.blog.naver.com/kimjw1218/70178629876
// tilt_cam functions 

//roll_rotate
// t_vec xaxis_rotate(t_vec point)

//pitch_rotate
// tilt updown
// [	1			0			0			0	]
// [	0		cos pitch	-sin pitch		0	]
// [	0		sin pitch	cos pitch		0	]
// [	0			0			0			1	]
//assume point is [x, y, z, 1]
t_vec _xaxis_rotate(t_vec point, double sin, double cos)
{
	t_vec	temp;

	temp.x = point.x;
	temp.y = point.y * cos - point.y * sin;
	temp.z = point.z * sin + point.z * cos;
	return (temp);
}


void	xaxis_rotate(t_camera *cam, double sin, double cos)
{
	t_vec	temp;
	t_vec point;

	point = vsub(cam->orig, cam->dir);
	temp.x = point.x;
	temp.y = point.y * cos - point.y * sin;
	temp.z = point.z * sin + point.z * cos;
	cam->dir = vadd(cam->orig, temp);
}


//yaw_rotate
// [	cos yaw		0		sin yaw			0	]
// [	0			1			0			0	]
// [	-sin yaw	0		cos yaw			0	]
// [	0			0			0			1	]
//tilt right/left
t_vec _yaxis_rotate(t_vec point, double sin, double cos)
{
	t_vec	temp;

	temp.x = point.x * cos + point.x * sin;
	temp.y = point.y;
	temp.z = - point.z * sin + point.x * cos;
	return (temp);
}

void	yaxis_rotate(t_camera *cam, double sin, double cos)
{
t_vec	temp;
	t_vec point;

	point = vadd(vec(20, 20, 20), cam->dir);
	print_vec (point);
	temp.x = point.x * cos + point.x * sin;
	temp.y = point.y;
	temp.z = - point.z * sin + point.x * cos;
	cam->dir = vsub(temp, vec(1, 1, 1));
	// cam->vup.x = cam->vup.x * cos + cam->vup.x * sin;
	// cam->vup.y = cam->vup.y;
	// cam->vup.z = - cam->vup.z * sin + cam->vup.x * cos;
}
