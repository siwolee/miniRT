/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 19:23:38 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/21 18:21:51 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cylinder	*cylinder(t_point center, t_vec dir, double dia, double height)
{
	t_cylinder	*cy;
	if (!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
		return (NULL);
	cy->center = center;
	cy->dir = dir;
	cy->dia = dia;
	cy->height = height;
	return (cy);
}

int	cy_boundary(t_cylinder *cy, t_vec at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vdot(vsub(at_point, cy->center), cy->dir);
	//나누기 2를 추가하였습니다 .
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (0);
	return (1);
}

t_vec	get_cylinder_normal(t_cylinder *cy, t_vec at_point, double hit_height)
{
	t_point	hit_center;
	t_vec	normal;

	hit_center = vadd(cy->center, vmuln(cy->dir, hit_height));
	normal = vsub(at_point, hit_center);

	return (vunit(normal));
}

int      hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, double height)
{
    const t_cylinder *cy = cy_obj->element;
    const double r = cy->dia / 2;
    const t_vec    circle_center = vadd(cy->center, vmuln(cy->dir, height));
    const float root = vdot(vsub(circle_center, ray->orig), cy->dir) / vdot(ray->dir, cy->dir);
    const float diameter = vlength(vsub(circle_center, ray_at(ray, root)));
	if (fabs(r) < fabs(diameter))
		return (0);
    if (root < rec->tmin || rec->tmax < root)
       return (0);
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->tmax = rec->t;
    if (0 < height)
        rec->normal = cy->dir;
    else
        rec->normal = vmuln(cy->dir, -1);

    // rec->normal = vunit(vminus(circle_center, ray->origin)); // vmult(ray->dir, root)하면 안돼!!!
    set_face_normal(ray, rec);
    rec->albedo = cy_obj->albedo;
    return (1);
}

int      hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cy;


    //a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
    double  a;
		double  half_b;
    double  c;
    t_vec  u;
    t_vec  o;
    t_vec  delta_P;
    double r;

    double discriminant; // 판별식
    double sqrtd;
    double root;
    double hit_height;

    cy = cy_obj->element;
    u = ray->dir;
    o = cy->dir;
    r = cy->dia / 2;
    delta_P = vsub(ray->orig, cy->center);
    a = vlength2(vcross(u, o));
    half_b = vdot(vcross(u, o), vcross(delta_P, o));
    c = vlength2(vcross(delta_P, o)) - pow(r, 2);
    discriminant = half_b * half_b - a * c;
    if (discriminant < 0)
        return (0);
    // 이 시점에서 판별식이 참이 나왔기에 근이 존재한다고 판단한다.
    sqrtd = sqrt(discriminant);
    root = (-half_b - sqrtd) / a;  // 근의 공식 해, 작은 근부터 고려.
    if (root < rec->tmin || rec->tmax < root)
    {
    root = (-half_b + sqrtd) / a;
        if (root < rec->tmin || rec->tmax < root)
        return (0);
    }
    //    print_vec(vmult(ray->dir, root));
    // print_vec(ray_at(ray, root));
    if (!(hit_height = cy_boundary(cy, ray_at(ray, root))))
        return (0);

    rec->t = root; // 광선의 원점과 교점까지의 거리를 rec에 저장한다.
    rec->p = ray_at(ray, root); // 교점의 좌표를 rec에 저장한다.
    rec->normal = get_cylinder_normal(cy, rec->p, hit_height);
	  set_face_normal(ray, rec);
    rec->albedo = cy_obj->albedo;
    return (1);
}

// int	hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, double height)
// {
// 	t_cylinder	*cy;
// 	double	r;
// 	t_vec	circle_center;
// 	double	root;
// 	double	diameter;

// 	cy = cy_obj->element;
// 	r = cy->dia / 2;
// 	//printf("%lf\n", cy->dir.z);
// 	circle_center = vadd(cy->center, vmuln(cy->dir, height));
// 	printf("%lf\n",circle_center.z);
// 	//방향벡터 정규화가 안되어있다?
// 	//원래식
// 	//root = vdot(vsub(circle_center, ray->orig), cy->dir);
// 	//이렇게하니까보이기는하더라
// 	root = vdot(vsub(circle_center, ray->orig), cy->dir) / vdot(ray->dir, cy->dir);
// 	diameter = vlength(vsub(circle_center, ray_at(ray, root)));
// 	if (fabs(r) < fabs(diameter))
// 		return (0);
// 	if (root < rec->tmin || rec->tmax < root)
// 		return (0);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	rec->tmax = rec->t;
// 	if (0 < height)
// 		rec->normal = cy->dir;
// 	else
// 		rec->normal = vmuln(cy->dir, -1);
// 	set_face_normal(ray, rec);
// 	rec->albedo = cy_obj->albedo;
// 	return (1);
// }

// int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_cylinder *cy;

// 	double	a;
// 	double	half_b;
// 	double	c;
// 	t_vec	u;
// 	t_vec	o;
// 	t_vec	delta_p;
// 	double	r;

// 	double	discriminant;
// 	double	sqrtd;
// 	double	root;
// 	double	hit_height;

// 	cy = cy_obj->element;
// 	// hit_height = cy->height;
// 	u = ray->dir;
// 	o = cy->dir;
// 	r = cy->dia / 2;
// 	delta_p = vsub(ray->orig, cy->center);
// 	a = vlength2(vcross(u, o));
// 	half_b = vdot(vcross(u, o), vcross(delta_p, o));
// 	c = vlength2(vcross(delta_p, o)) - pow(r, 2);
// 	discriminant = half_b * half_b - a * c;
// 	if (discriminant < 0)
// 		return (0);
// 	sqrtd = sqrt(discriminant);
// 	root = (-half_b - sqrtd) / a;
// 	if (root < rec->tmin || rec->tmax < root)
// 	{
// 		root = (-half_b + sqrtd) / a;
// 		if (root < rec->tmin || rec->tmax < root)
// 			return (0);
// 	}
// 	//위아래 높이 찾아주는 부분
// 	if (!(hit_height = cy_boundary(cy, ray_at(ray, root))))
// 		return (0);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	rec->normal	= get_cylinder_normal(cy, rec->p, hit_height);
// 	set_face_normal(ray, rec);
// 	rec->albedo = cy_obj->albedo;
// 	return (1);
// }

//조건문
t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder	*cy;
	int	result;

	cy = (t_cylinder *)cy_obj->element;
	//printf("dia : %lf height : %lf\n", cy->dia, cy->height);
	result = 0;
	//height/2 수정하고 위에서 추가함
	result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2);
	result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2));
	//저거 height /2가 빠져있었네? 니가그랬냐?
	result += hit_cylinder_side(cy_obj, ray, rec);
	if (result > 0)
		return (TRUE);
	else
		return (FALSE);
	// return (result);
}
