#include <gjk.h>
#include <physic.h>

/*
** data is a t_entity pointer
*/

int	entity_direction(t_vec3d *direction, void *data)
{
	t_entity	*e;

	e = (t_entity*)data;
	if (vec3_magnitude(e->velocity) > 0.0)
	{
		*direction = e->velocity;
		return (1);
	}
	return (0);
}
