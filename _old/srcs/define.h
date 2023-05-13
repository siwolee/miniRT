/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 20:34:51 by siwolee           #+#    #+#             */
/*   Updated: 2023/05/02 17:35:05 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

// # include "ray.h"
// # include "vec3.h"
// # include "type.h"

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# define TRUE 0
# define FALSE 1

typedef struct s_hit_record
{
	float	t;
	t_vec	p;
	t_vec	normal;
}	t_hit_record;


//물체들을 통합해서 가지고 있는 리스트.
//data는 각 물체의 포인터를 가지고
//type은 무슨 물체인지 알려줌
typedef struct s_hitable
{
	void			*data;
	int 			type;
	struct s_hitable	*next;
	struct s_hitable	*prev;

}	t_hitable;

typedef int t_bool;

enum
{
	TYPE_NULL,
	TYPE_PLANE,
	TYPE_SPHERE,
	TYPE_CYLINDER
};

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}t_vec;

typedef t_vec	t_point;
typedef t_vec	t_color;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	int	*data;
	int bpp;
	int size_l;
	int endian;
}	t_mlx;

typedef struct s_ambient
{
	double		range;
	t_color		color;
}			t_ambient;

typedef struct s_camera
{
	// t_point			point;
	t_point			origin;
	// t_vec			vec;
	t_vec			direction;
	t_vec			lower_left_corner;
	t_vec			horizental;
	t_vec			vertical;
	// t_vec			vup; //??
	// double			vfov; //top of top to bottom in degrees
	// double			aperture; //??
	// double			focus_distance;
	// double			degree; //화각
	//anti_aliasing
	// double			time0;
	// double			time1;
	struct s_camera	*next;
}			t_camera;


typedef struct s_light
{
	t_point			point;
	double			bright;
	t_color			color;
	struct s_light	*next;
}			t_light;


//hitable에 다음 도형 정보 저장되고 있으므로
//아래 도형 정보에서 next 뺌

typedef struct s_plane
{
	t_point			point;
	t_vec			vec;
	t_color			color;
}				t_plane;

typedef struct s_sphere
{
	t_point			point;
	// double			dia;
	// dia를 계산할 때  쓰지  않아서  radius로 넣어두는 게 편함
	double			radius
	t_color			color;
}			t_sphere;

typedef struct s_cylinder
{
	t_point				point;
	t_vec				vec;
	t_color				color;
	double				dia;
	double				height;
}	t_cylinder;

// typedef struct s_main
// {
// 	t_ambient	ambient;
// 	t_camera	*cam;
// 	t_light		*light;
// 	t_plane		*plane;
// 	t_sphere	*sphere;
// 	t_cylinder	*cylinder;
// }t_main;


typedef struct	s_scene
{
	t_ambient 	ambient;
	t_camera	*cam;
	t_light		light;
	t_hitable	hitable;
	// 일단 test.c main에서 쓰던 거 가져옴
	double		aspect_ratio;
	double		image_width;
	double		image_height;
	float		viewport_height;
	float		viewport_width;
	double		focal_length;
}	t_scene;

#endif