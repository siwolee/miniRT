/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:49:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/04/24 21:58:28 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum {
	AMB,
	CAM,
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER
}

typedef struct s_mlx
{
	void *mlx;
	void *win; 
	void *img;
	int	*data;
	int bpp;
	int size_l;
	int endian;
	int color[3];
}t_mlx;

typedef struct s_vec
{
	double x;
	double y;
	double z;
}t_vec;

typedef struct s_point
{
	double x;
	double y;
	double z;
}t_point;

typedef struct s_color
{
	double r;
	double b;
	double g;
}t_color;

typedef struct s_ambient
{
	double		range;
	double		r;
	double		g;
	double		b;
}			t_ambient;

typedef struct s_camera
{
	double			crd_x;
	double			crd_y;
	double			crd_z;
	double			vec_x;
	double			vec_y;
	double			vec_z;
	double			fov;
	struct s_camera	*next;
}			t_camera;


typedef struct s_light
{
	double			crd_x;
	double			crd_y;
	double			crd_z;
	double			bright;
	double			r;
	double			g;
	double			b;
	struct s_light	*next;
}			t_light;

typedef struct s_plane
{
	double			crd_x;
	double			crd_y;
	double			crd_z;
	double			vec_x;
	double			vec_y;
	double			vec_z;
	double			r;
	double			g;
	double			b;
	struct s_plane	*next;
}				t_plane;

typedef struct s_sphere
{
	double			crd_x;
	double			crd_y;
	double			crd_z;
	double			dia; // 판별식에서 rad로 쓰고 있는데, dia 쓸 일이 있을지...
	double			r;
	double			g;
	double			b;
	struct s_sphere	*next;
}			t_sphere;

typedef struct s_cylinder
{
	double				crd_x;
	double				crd_y;
	double				crd_z;
	double				vec_x;
	double				vec_y;
	double				vec_z;
	double				dia;
	double				height;
	double				r;
	double				g;
	double				b;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_main
{
	t_ambient	ambient;
	t_camera	*cam;
	t_light		*light;
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
}t_main;

#endif
