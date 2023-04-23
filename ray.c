#include "vec3.h"
#include "ray.h"

void 	*ray_init_vec(t_ray *r, void *origin, void *direction)
{
	r->origin = (t_point *)origin;
	r->direction = (t_vec *)direction;
}

void 	*ray_init_zero(t_ray *r)
{

	r->origin = (t_point *)origin;
	r->direction = (t_vec *)direction;
}

t_vec	*ray_at(t_ray *ray, double t)
{
	t_point	*temp;

	temp = malloc(sizeof(t_ray));
	if (!temp)
		return (0);
	temp->x = ray->direction->x * t + ray->origin->x;
	temp->y = ray->direction->y * t + ray->origin->y;
	temp->z = ray->direction->z * t + ray->origin->z;
	return (temp);
}