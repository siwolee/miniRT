/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:49:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/03 19:53:06 by juhyulee         ###   ########.fr       */
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

extern void* __debug_tmp__;
# define malloc(x) \
(__debug_tmp__ = malloc(x)); \
printf("%s:%d %p [%lubyte]\n", __FILE__, __LINE__, __debug_tmp__, x)

enum e_error_code
{
	ERROR_NO_INPUT,
	ERROR_CANNOT_OPEN_FILE,
	ERROR_FILE_TYPE,
	ERROR_PARSE,
	ERROR_NO_ELEMENT
};
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}t_vec;

typedef int		t_object_type;
typedef int		t_bool;
typedef t_vec	t_point;
typedef t_vec	t_color;

# define SP 0
# define LIGHT_POINT 1
# define PL 2
# define CY 3
# define VAL 5

# define EPSILON 1e-6 //0.000001
# define LUMEN 3 //광원들의 밝기

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		line_length;
	int		size_l;
	int		endian;
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
typedef struct s_ray
{
	t_point	orig;
	t_vec	dir;
	float	t_min;
	float	t_max;
}	t_ray;

typedef struct s_cy_temp
{
	double	a;
	double	half_b;
	double	c;
	t_vec	u;
	t_vec	o;
	t_vec	delta_p;
	double	r;
	double	discriminant;
	double	sqrtd;
	double	root;
	double	hit_height;
}		t_cy_temp;

typedef struct s_light_temp
{
	t_color	diffuse;
	t_vec	light_dir;
	double	kd;
	t_color	specular;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	light_len;
	t_ray	light_ray;
	double	spec;
	double	ksn;
	double	ks;
	double	brightness;
}		t_light_temp;
typedef struct s_sphere
{
	t_point	center;
	double	radius;
	double	radius2;
}		t_sphere;

typedef struct s_sphere_temp
{
	t_vec		oc;
	t_sphere	*sp;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;
}		t_sphere_temp;
typedef struct s_cylinder
{
	t_point				center;
	t_vec				dir;
	double				dia;
	double				height;
}	t_cylinder;

typedef struct s_hit_record
{
	t_point	p;
	t_vec	normal;
	double	tmin;
	double	tmax;
	double	t;
	t_bool	front_face;
	t_color	albedo;
}		t_hit_record;

typedef struct s_object
{
	t_object_type		type;
	void				*element;
	struct s_object		*next;
	t_color				albedo;
}	t_object;

typedef struct s_light
{
	t_point	origin;
	t_color	light_color;
	double	bright_ratio;
}	t_light;

typedef struct s_camera
{
	t_point			orig;
	t_vec			dir;
	double			aspect;
	t_vec			vup;
	double			viewport_h;
	double			viewport_w;
	t_vec			horizontal;
	t_vec			vertical;
	t_point			left_bottom;
	double			fov;
	double			focal_len;
	struct s_camera	*next;
}t_camera;

typedef struct s_canvas
{
	int		width;
	int		height;
	double	aspect_ratio;
}		t_canvas;

typedef struct s_scene
{
	t_canvas		canvas;
	t_camera		*camera;
	t_object		*world;
	t_object		*light;
	t_color			ambient;
	t_ray			ray;
	t_hit_record	rec;
	int				canvas_height;
	int				canvas_width;
}		t_scene;
typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	image;
	t_scene	scene;
}	t_vars;

//parse
void		readmap(t_scene *scene, int fd);
t_vec		parse_point(char **split);
t_vec		parse_vec(char **split);
t_vec		parse_vec_normalize_color(char **split);
int			file_check(int ac, char **av);
t_scene		scene_init(void);
double		ft_(const char *str);
char		*valid_parse_vec(char *str);
void		free_split(char **split);
void		input_cylinder(t_scene *scene, char *str);
void		input_sphere(t_scene *scene, char *str);
void		input_camera(t_scene *scene, char *str);
void		input_ambient(t_scene *scene, char *str);
void		input_plane(t_scene *scene, char *str);
void		convert_space(char *c);
double		ft_atod(const char *str);
int			read_mapsize(int fd, t_scene *scene);

//error
void		exit_error(int code);

//free
void		free_vars(t_vars *vars);

//vecter
void		vprint(char *name, t_vec v);
t_vec		vmin(t_vec vec1, t_vec vec2);
t_vec		vunit(t_vec vec);
t_vec		vcross(t_vec vec, t_vec vec2);
double		vdot(t_vec vec, t_vec vec2);
t_vec		vdivn(t_vec vec, double t);
t_vec		vmulv(t_vec vec, t_vec vec2);
t_vec		vmuln(t_vec vec, double t);
t_vec		vsubn(t_vec vec, double x, double y, double z);
t_vec		vsub(t_vec vec, t_vec vec2);
t_vec		vaddn(t_vec vec, double x, double y, double z);
t_vec		vadd(t_vec vec, t_vec vec2);
double		vlength(t_vec vec);
double		vlength2(t_vec vec);
void		vset(t_vec *vec, double x, double y, double z);
t_vec		vec(double x, double y, double z);
t_vec		reflect(t_vec v, t_vec n);
void		print_vec(t_vec t);
t_vec		parse_point(char **split);

//camera
t_canvas	canvas(int width, int height);
t_camera	*camera(t_point lookfrom, t_vec lookat, double fov, double aspect);
void		move_camera(t_camera *cam, t_vec vup);

//ray
t_ray		ray(t_point orig, t_vec dir);
t_point		ray_at(t_ray *ray, double t);
t_ray		ray_primary(t_camera *cam, double u, double v);
t_color		ray_color(t_scene *scene);
void		set_face_normal(t_ray *r, t_hit_record *rec);

//sphere
t_sphere	*sphere(t_point center, double radius);
t_bool		hit_sphere(t_object *sp_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);

//object
t_object	*object(t_object_type type, void *element, t_color albedo);
t_object	*olast(t_object *list);
void		oadd(t_object **list, t_object *new);

//light
t_light		*light_point(t_point light_origin, t_color light_color, \
double bright_ratio);
t_color		phong_lighting(t_scene *scene);
t_color		point_light_get(t_scene *scene, t_light *light);
t_bool		in_shadow(t_object *objs, t_ray light_ray, double light_len);

//plane
t_bool		hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec);
t_plane		*plane(t_point center, t_vec dir);

//cylinder
t_cylinder	*cylinder(t_point center, t_vec dir, double dia, double height);
t_vec		get_cylinder_normal(t_cylinder *cy, t_vec at_point, \
double hit_height);
int			hit_cylinder_cap(t_object *cy_obj, t_ray *ray, \
t_hit_record *rec, double height);
int			hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
t_bool		hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
void		cy_temp_struct(t_cy_temp *temp, t_cylinder *cy, t_ray *ray);
int			hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec);
int			cy_boundary(t_cylinder *cy, t_vec at_point);

//mlx
int			key_press(int keycode, t_vars *vars);
void		ft_init_mlx(t_vars *vars, t_scene *scene, t_data *image);
void		ft_draw(t_scene *scene, t_data *image);

#endif
