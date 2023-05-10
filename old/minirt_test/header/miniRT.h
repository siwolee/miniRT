/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:49:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/07 15:25:22 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# define TRUE 0
# define FALSE 1

typedef int	t_object_type;
# define SP 0
# define LIGHT_POINT 1

# define EPSILON 1e-6 //0.000001
# define LUMEN 3 //광원들의 밝기

typedef int t_bool;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}t_vec;

typedef t_vec	t_point;
typedef t_vec	t_color;

typedef struct s_ambient
{
	double		range;
	t_color		color;
}			t_ambient;

// typedef struct s_camera
// {
// 	t_point			origin;
// 	t_vec			vec;
// 	t_vec			right;
// 	t_vec			up;
// 	t_point			left;
// 	double			fov;
// 	double			len;
// 	struct s_camera	*next;
// }			t_camera;


// typedef struct s_light
// {
// 	t_point			point;
// 	double			bright;
// 	t_color			color;
// 	struct s_light	*next;
// }			t_light;

typedef struct s_plane
{
	t_point			point;
	t_vec			vec;
	t_color			color;
	struct s_plane	*next;
}				t_plane;

// typedef struct s_sphere
// {
// 	t_point			point;
// 	double			dia;
// 	t_color			color;
// 	struct s_sphere	*next;
// }			t_sphere;

typedef struct s_cylinder
{
	t_point				point;
	t_vec				vec;
	t_color				color;
	double				dia;
	double				height;
	struct s_cylinder	*next;
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

typedef struct s_ray
{
	t_point	origin;
	t_vec	direction;
	float	t_min;
	float	t_max;
}	t_ray;

typedef struct s_sphere
{
	t_point	center;
	double	radius;
	double	radius2;
}		t_sphere;

typedef struct s_hit_record
{
	t_point	p; //충돌 지점 좌표
	t_vec	normal; //교점에서 나온 법선
	double	tmin; // 기본 0, 물체가 뒤에 있을 경우에는 감지하지 않는다
	double	tmax; //광선 가시거리, 일
	double	t;	//광선의 원점과 교점 사이의 거리
	t_bool	front_face;
	t_color	albedo;
}		t_hit_record;

typedef struct	s_object
{
	t_object_type	type;
	void			*element;
	void			*next;
	t_color			albedo;
}	t_object;

typedef struct s_light
{
	t_point	origin; //빛 좌좌표표
	t_color	light_color; //빛 색
	double	bright_ratio;
}	t_light;

typedef struct  s_camera
{
	t_point    origin;  // 카메라 원점(위치)
	t_vec      dir; // 카메라 벡터
	t_vec      right_normal; // 카메라 벡터가 평면이 아닐 때의 left_bottom을 구하기 위해
	t_vec      up_normal; // 카메라 벡터가 평면이 아닐 때의 left_bottom을 구하기 위해
	t_point    left_bottom; // 왼쪽 아래 코너점

	double      fov;       // 화각
	double      focal_len; // 화각에 따라 카메라와 viewport와의 거리가 달라진다.
}t_camera;

typedef struct	s_scene
{
	t_camera	camera;
	t_object	*world;
	t_light		*light;
	t_color		ambient;
	t_ray		ray;
	t_hit_record	rec;
}		t_scene;



t_vec	unit_vecter(t_vec u);
t_vec	v_create(double x, double y, double z);
t_vec	v_mul_n(t_vec u, double t);
t_vec	v_add(t_vec u, t_vec v);
t_vec	v_sub(t_vec u, t_vec v);
t_vec	v_cross(t_vec v1, t_vec v2);
double	dot(t_vec u, t_vec v);
double	length(t_vec u);
t_sphere    *sphere(t_point center, double radius);
void	print_vec(t_vec v);
double	length_squared(t_vec u);
t_point	ray_at(t_ray *r, double t);
t_vec	v_div(t_vec u, double t);
t_bool	hit_sphere(t_object *world, t_ray *ray, t_hit_record *rec);
t_object	*olast(t_object *list);
void	oadd(t_object **list, t_object *new);
t_bool	hit(t_object *world, t_ray *ray, t_hit_record *rec);
t_bool	hit_obj(t_object *world, t_ray *ray, t_hit_record *rec);
t_object	*object(t_object_type type, void *element, t_color albedo);
t_color ray_color(t_scene *scene);
t_vec  v_min(t_vec vec1, t_vec vec2);
t_vec      v_mul_v(t_vec vec, t_vec vec2);
t_vec	reflect(t_vec v, t_vec n);

#endif
