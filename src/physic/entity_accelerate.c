#include <physic.h>
#include <world.h>

t_vec3d	entity_accelerate(t_entity e, t_vec3d a)
{
	t_vec3d	t;
	// double	d;

	// d = vec3_dot(vec3_normalize(e.velocity), vec3_normalize(a));
	// if (d > 0 && d <= 1)
	// 	t = vec3vec3_add(e.velocity, vec3scalar_multiply(a, d));
	// else
		t = vec3vec3_add(e.velocity, a);
	if (vec3_dot(t, t) <= e.sector->physics.speed_limit * e.sector->physics.speed_limit)
		return (t);
	return (e.velocity);
}
