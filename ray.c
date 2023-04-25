#include "vec3.h"
#include "ray.h"

void 	ray_init_vec(t_ray *r, void *origin, void *direction)
{
	r->origin = (t_point *)origin;
	r->direction = (t_vec *)direction;
	r->t_min = T_MIN;
	r->t_max = T_MAX;
}

void 	ray_init_zero(t_ray *r)
{
	t_point *origin;
	t_vec	*direction;

	origin = vec_init_new(0, 0, 0);
	direction = vec_init_new(0, 0, 0);
	r->origin = (t_point *)origin;
	r->direction = (t_vec *)direction;
	r->t_min = T_MIN;
	r->t_max = T_MAX;
}

void	*ray_at(t_ray *ray, double t)
{
	t_point	*temp;

	temp = malloc(sizeof(t_vec));
	if (!temp)
		return (0);
	temp->x = ray->direction->x * t + ray->origin->x;
	temp->y = ray->direction->y * t + ray->origin->y;
	temp->z = ray->direction->z * t + ray->origin->z;
	return (temp);
}