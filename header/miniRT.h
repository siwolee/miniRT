/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:49:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/24 15:16:36 by siwolee          ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0
# define X_EVENT_KEY_EXIT	17

enum error_code
{
	ERROR_NO_INPUT,
	ERROR_CANNOT_OPEN_FILE,
	ERROR_FILE_TYPE,
	ERROR_PARSE,
	ERROR_NO_ELEMENT
};

typedef int	t_object_type;

# define SP 0
# define LIGHT_POINT 1
# define PL 2
# define CY 3

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

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		line_length;
	int 	size_l;
	int 	endian;
}	t_mlx;


typedef struct s_ambient
{
	double		range;
	t_color		color;
}			t_ambient;

typedef struct s_plane
{
	t_point	center;
	t_vec	dir;
}				t_plane;

typedef struct s_cylinder
{
	t_point				center;
	t_vec				dir;
	double				dia;
	double				height;
}	t_cylinder;

typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
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
	t_object_type		type;
	void				*element;
	struct	s_object	*next;
	t_color				albedo;
}	t_object;

typedef struct s_light
{
	t_point	origin; //빛 좌좌표표
	t_color	light_color; //빛 색
	double	bright_ratio;
}	t_light;

typedef struct  s_camera
{
	t_point		orig;  // 카메라 원점(위치)
	t_vec		dir; // 카메라 벡터
	double		aspect;//추가
	t_vec		vup; //ㅊㅜ가
	double		viewport_h;
	double		viewport_w;
	t_vec		horizontal;
	t_vec		vertical;
	t_point		left_bottom;
	double      fov;       // 화각
	double      focal_len; // 화각에 따라 카메라와 viewport와의 거리가 달라진다.
}t_camera;

typedef struct s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //종횡비
}		t_canvas;


typedef struct	s_scene
{
	t_canvas	canvas;
	t_camera	*camera;
	t_object	*world;
	t_object	*light;
	t_color		ambient;
	t_ray		ray;
	t_hit_record	rec;
	int			canvas_height;//추가 05.10
	int			canvas_width;//추가 05.10 by sw
}		t_scene;

//parse
void	readmap(t_scene *scene, int fd);

//error
void	exit_error(int code);

//vecter
void	vprint(char *name, t_vec v);
t_vec  vmin(t_vec vec1, t_vec vec2);
t_vec	vunit(t_vec vec);
t_vec	vcross(t_vec vec, t_vec vec2);
double	vdot(t_vec vec, t_vec vec2);
t_vec	  vdivn(t_vec vec, double t);
t_vec	  vmulv(t_vec vec, t_vec vec2);
t_vec	vmuln(t_vec vec, double t);
t_vec	  vsubn(t_vec vec, double x, double y, double z);
t_vec	  vsub(t_vec vec, t_vec vec2);
t_vec	  vaddn(t_vec vec, double x, double y, double z);
t_vec	vadd(t_vec vec, t_vec vec2);
double	 vlength(t_vec vec);
double	vlength2(t_vec vec);
void	vset(t_vec *vec, double x, double y, double z);
t_vec	vec(double x, double y, double z);
t_vec	reflect(t_vec v, t_vec n);
void	print_vec(t_vec t);
t_vec	parse_point(char **split);

//camera
t_canvas	canvas(int width, int height);
t_camera *camera(t_point lookfrom, t_vec lookat, double fov, double aspect);
void	move_camera(t_camera *cam, t_vec vup);

//ray
t_ray	ray(t_point orig, t_vec dir);
t_point	ray_at(t_ray *ray, double t);
t_ray	ray_primary(t_camera *cam, double u, double v);
t_color	ray_color(t_scene *scene);
void	set_face_normal(t_ray *r, t_hit_record *rec);

//sphere
t_sphere	*sphere(t_point center, double radius);
t_bool	hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
t_bool	hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool	hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);

//object
t_object	*object(t_object_type type, void *element, t_color albedo);
t_object	*olast(t_object *list);
void	oadd(t_object **list, t_object *new);

//light
t_light	*light_point(t_point light_origin, t_color light_color, double bright_ratio);
t_color	phong_lighting(t_scene *scene);
t_color	point_light_get(t_scene *scene, t_light *light);
t_bool	in_shadow(t_object *objs, t_ray light_ray, double light_len);

//plane
t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
t_plane	*plane(t_point center, t_vec dir);

//cylinder
t_cylinder	*cylinder(t_point center, t_vec dir, double dia, double height);
t_vec	get_cylinder_normal(t_cylinder *cy, t_vec at_point, double hit_height);
int	hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, double height);
int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec);



#endif
