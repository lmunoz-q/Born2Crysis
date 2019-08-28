#include <gjk.h>
#include <physic.h>

/*
** data is a t_wall pointer
*/

int	wall_direction(t_vec3d *direction, void *data)
{
	*direction = ((t_wall*)data)->normal;
	return (1);
}
