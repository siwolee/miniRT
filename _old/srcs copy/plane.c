/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:56:05 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/05 20:32:02 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{//pl_obj : 평면 구조체
    t_plane *pl = pl_obj->element;
    float numrator; // 판별식의 분자
    float denominator; // 판별식의 분모
    float root;
    denominator = vdot(ray->dir, pl->normal); // 광선 벡터와 평면의 방향벡터 내적
    if (denominator < EPSILON) // 분모의 값이 0보다 작거나 같을 경우 충돌하지 않는다.
        return (FALSE);
    numrator = vdot(vminus(pl->point, ray->orig), pl->normal);//평면의 중심에서 광선의 원점을 뺀다음 평면의 방향벡터와 내적
    root = numrator / denominator;
    if (root < rec->tmin || rec->tmax < root)
        return (FALSE);
    rec->t = root;
    rec->p = ray_at(ray, root);
    // rec->normal = pl->normal;
    rec->albedo = pl_obj->albedo;//색상값
    // print_vec(normal);
    return (TRUE);
}
