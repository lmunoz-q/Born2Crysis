#include <physic.h>

/*
** takes a face's normal and determine if it falls in one of four categories:
** ceiling, floor, wall X, wall Z
** Y is positive UP and negative DOWN
 */

t_wall_type	wall_type(t_double3 normal)
{
	t_double3	abs;

	abs = (t_double3){.x = (normal.x < 0.0) ? -normal.x : normal.x,
		.y = (normal.y < 0.0) ? -normal.y : normal.y,
		.z = (normal.z < 0.0) ? -normal.z : normal.z};
	if (abs.y > WALL_TOLERANCE)
		return (normal.y > 0 ? WT_FLOOR : WT_CEIL);
	return (abs.x > abs.z ? WT_WALL_X : WT_WALL_Z);
}