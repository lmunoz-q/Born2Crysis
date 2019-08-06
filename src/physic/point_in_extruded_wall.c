#include <physic.h>

/*
** extrusion: x: size of the extrusion, displacement (along the normal) of the extrusion
*/

/*
** new version: the extrusion is calculated based on the width of the entity
** return values: 0 no collisions, 1 feet collision against floor, 2 feet collision against ramp, 3 feet collision against wall, 4 head collision against wall, 5 head collision against ceiling
** the correction returned is a multiplicator to the normal of the wall to apply
** on the entity to get it out of the wall
*/

// int	point_in_extruded_wall(t_vec3d point, t_wall wall, t_vec2d extrusion, double *correction)
int	entity_wall_collision(t_entity original, t_entity ent, t_wall wall, double *correction)
{
	t_vec3d		v;
	double		d;
	t_vec3d		p;
	double		dots[3];
	double		y;

	(void)original;
	y = vec3_dot((t_vec3d){.a = {0, 1, 0}}, wall.normal);
	if (y > 0.0)
		ent.position.n.y += ent.height;
	v = vec3vec3_substract(ent.position, wall.center);
	d = vec3_dot(v, wall.normal);
	p = vec3vec3_substract(ent.position, vec3scalar_multiply(wall.normal, d));
	dots[0] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[1], wall.vertices[0]), wall.normal), wall.vertices[0], p);
	dots[1] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[2], wall.vertices[1]), wall.normal), wall.vertices[1], p);
	dots[2] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[0], wall.vertices[2]), wall.normal), wall.vertices[2], p);
	if ((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
		&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0))
		return (0);
	double md = (d < 0.0 ? -1.0 : 1.0) * vec3_magnitude(vec3vec3_substract(p, ent.position));
	double ec = (1.0 - fabs(y)) * ent.radius * 3.0;
	y = 180.0 / M_PI * acos(y);
	if (ent.radius < 1.0)
		ent.radius = 1.0;
	if (md >= ec || md <= -(ent.radius * 10.0 - ec))
		return (0);
	if (correction != NULL)
		*correction = ec - md;
	if (y < 30)
		return (1);
	if (y < 60)
		return (2);
	if (y < 90)
		return (3);
	if (y < 100)
		return (4);
	return (5);
}
