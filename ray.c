#include "vec3.h"

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