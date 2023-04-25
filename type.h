/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:49:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/04/25 13:57:45 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}t_vec;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}t_point;

typedef struct s_color
{
	double	x;
	double	y;
	double	z;
}t_color;

typedef struct s_ambient
{
	double		range;
	t_color		color;
}			t_ambient;

typedef struct s_camera
{
	t_point			point;
	t_vec			vec;
	double			fov;
	struct s_camera	*next;
}			t_camera;


typedef struct s_light
{
	t_point			point;
	double			bright;
	t_color			color;
	struct s_light	*next;
}			t_light;

typedef struct s_plane
{
	t_point			point;
	t_vec			vec;
	t_color			color;
	struct s_plane	*next;
}				t_plane;

typedef struct s_sphere
{
	t_point			point;
	double			dia;
	t_color			color;
	struct s_sphere	*next;
}			t_sphere;

typedef struct s_cylinder
{
	t_point				point;
	t_vec				vec;
	t_color				color;
	double				dia;
	double				height;
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
