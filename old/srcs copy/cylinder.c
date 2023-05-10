/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:41:42 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/05 20:32:01 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	cy_boundary(t_cylinder *cy, t_vec3 at_point, t_cylinops *c)
{//cy : 실린더 구조체, at+point : 광선의 원점 c : 실린더 옵션 -
	double	hit_height;
	double	max_height;

	hit_height = vdot(vminus(at_point, cy->center), cy->dir);
	max_height = cy->height / 2;
	c->hit_height = hit_height;
	if (fabs(c->hit_height) > max_height)
		return (0);
	return (1);
}

t_vec3      get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
    t_point3 hit_center;
    t_vec3 normal;

    hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
    normal = vminus(at_point, hit_center);

    return (vunit(normal));
}

int      hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, double height)
{//실린더 윗면 아랫면 부딫히는지 판별하는 함수
    const t_cylinder *cy = cy_obj->element;
    const double r = cy->diameter / 2;
    const t_vec3    circle_center = vplus(cy->center, vmult(cy->dir, height));
    const float root = vdot(vminus(circle_center, ray->origin), cy->dir)
	//원의 중심에서 광선의 원점을 뺀다음 실린더의 방향과 내적
    const float diameter = vlength(vminus(circle_center, ray_at(ray, root)));
	if (fabs(r) < fabs(diameter))
		return (0);
    if (root < rec->tmin || rec->tmax < root)
       return (0);
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->tmax = rec->t;
    if (0 < height)
        rec->normal = cy->dir;//원기둥의 방향 벡터
    else
        rec->normal = vmult(cy->dir, -1);

    // rec->normal = vunit(vminus(circle_center, ray->origin)); // vmult(ray->dir, root)하면 안돼!!!
    set_face_normal(ray, rec);
    rec->albedo = cy_obj->albedo;
    return (1);
}

int      hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    t_cylinder *cy;


    //a, b, c는 각각 t에 관한 근의 공식 2차 방정식의 계수
    double  a; //u와 o를 외적한 벡터의 제곱
	double  half_b; //u와 o의 외적한 벡터와 p와 o의 외적한 벡터를 내적
    double  c;//p와 o의 외적한 벡터의 제곱 - 원 반지름의 제곱
    t_vec3  u;//광선의 방향 벡터
    t_vec3  o;//원기둥의 방햐 ㅇ벡터
    t_vec3  delta_P;//광선의 원점 - 원기둥의 중심점
    double r;

    double discriminant; // 판별식
    double sqrtd;
    double root;
    double hit_height;

    cy = cy_obj->element;
    u = ray->dir;//광선의 방향 벡터
    o = cy->dir;//원기둥의 방향 벡터
    r = cy->diameter / 2;
    delta_P = vminus(ray->origin, cy->center);//광선의 원점 - 원기둥의 중심점
    a = vlength2(vcross(u, o));//u와 o를 외적하고 제곱
    half_b = vdot(vcross(u, o), vcross(delta_P, o));//u와 o의 외적한 벡터와 p와 o의 외적한 벡터를 내적
    c = vlength2(vcross(delta_P, o)) - pow(r, 2);//p와 o의 외적한 벡터의 제곱 - 원 반지름의 제곱
    discriminant = half_b * half_b - a * c; //판별식
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
    rec->albedo = cy_obj->albedo;//색상값
    return (1);
}

t_bool      hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
    const t_cylinder *cy = cy_obj->element;
    int result;

    result = 0;
    result += hit_cylinder_cap(cy_obj, ray, rec, cy->height / 2); //실린더 위쪽 원
    result += hit_cylinder_cap(cy_obj, ray, rec, -(cy->height / 2)); //실린더 밑면
    result += hit_cylinder_side(cy_obj, ray, rec); //실린더 옆면
    return (result);
}
