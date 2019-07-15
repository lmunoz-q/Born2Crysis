#include <physic.h>

t_double3	d3_add(t_double3 a, t_double3 b)
{
	return ((t_double3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z});
}

int	point_in_extruded_wall(t_double3 point, t_double3 wall[3], t_double3 extrusion_1, t_double3 extrusion_2)
{
	t_double3	f1[3];
	t_double3	f2[3];
	t_double3	n[5];

	f1[0] = d3_add(wall[0], extrusion_1);
	f1[1] = d3_add(wall[1], extrusion_1);
	f1[2] = d3_add(wall[2], extrusion_1);
	f2[0] = d3_add(wall[0], extrusion_2);
	f2[1] = d3_add(wall[1], extrusion_2);
	f2[2] = d3_add(wall[2], extrusion_2);
}