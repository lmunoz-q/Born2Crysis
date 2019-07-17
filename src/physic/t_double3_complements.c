#include <physic.h>

t_double3	d3_add(t_double3 a, t_double3 b)
{
	return ((t_double3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z});
}

t_double3	d3_substract(t_double3 a, t_double3 b)
{
	return ((t_double3){.x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z});
}

t_double3	d3_scale(t_double3 v, double s)
{
	return ((t_double3){.x = v.x * s, .y = v.y * s, .z = v.z * s});
}
