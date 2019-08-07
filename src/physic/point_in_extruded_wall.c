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

/*
** return the length of line needed to be aplied to l0 to find the intersection
** might return invalid values with line paralel to the plane
*/

double	line_plane_intersection(t_vec3d normal, t_vec3d p0, t_vec3d line, t_vec3d l0)
{
	return (vec3_dot(vec3vec3_substract(p0, l0), normal) / vec3_dot(normal, line));
}

// int	point_in_extruded_wall(t_vec3d point, t_wall wall, t_vec2d extrusion, double *correction)
int	entity_wall_collision(t_entity original, t_entity ent, t_wall wall, double *correction)
{
	double d;
	t_vec3d p;
	double dots[3];
	double y;
	double ec;
	double continuous;

	y = vec3_dot((t_vec3d){.a = {0, 1, 0}}, wall.normal);
	ec = (1.0 - fabs(y)) * ent.radius * 3.0;
	if (ent.radius < 1.0)
		ent.radius = 1.0;
	if (y < 0.0)
	{
		ent.position.n.y += ent.height;
		original.position.n.y += original.height;
	}
	d = vec3_dot(vec3vec3_substract(ent.position, wall.center), wall.normal);
	double t = vec3_dot(vec3vec3_substract(original.position, wall.center), wall.normal);
	if (ec - t >= ec - d)
		return (0);
	continuous = line_plane_intersection(wall.normal, wall.center, vec3vec3_substract(original.position, ent.position),
		original.position);
	if (continuous > 0.0 && continuous <= 1.0)
	{
		p = vec3vec3_add(original.position,
			vec3scalar_multiply(vec3vec3_substract(original.position, ent.position), continuous));
		dots[0] = dist_pointplane(
			vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[1], wall.vertices[0]), wall.normal),
			wall.vertices[0], p);
		dots[1] = dist_pointplane(
			vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[2], wall.vertices[1]), wall.normal),
			wall.vertices[1], p);
		dots[2] = dist_pointplane(
			vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[0], wall.vertices[2]), wall.normal),
			wall.vertices[2], p);
		if (!((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
			&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0)))
			continuous = 0.42;
	}
	if (continuous != 0.42)
	{
		p = vec3vec3_substract(ent.position, vec3scalar_multiply(wall.normal, d));
		dots[0] = dist_pointplane(
			vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[1], wall.vertices[0]), wall.normal),
			wall.vertices[0],
			p);
		dots[1] = dist_pointplane(
			vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[2], wall.vertices[1]), wall.normal),
			wall.vertices[1],
			p);
		dots[2] = dist_pointplane(
			vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[0], wall.vertices[2]), wall.normal),
			wall.vertices[2],
			p);
		if ((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
			&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0))
			return (0);
		if (d >= ec || d <= -(ent.radius * 10.0 - ec))
			return (0);
	}
	if (correction != NULL)
		*correction = ec - d;
	y = 180.0 / M_PI * acos(y);
	if (y < 30.0)
		return (1);
	if (y < 60.0)
		return (2);
	if (y < 90.0)
		return (3);
	if (y < 100.0)
		return (4);
	return (5);
}
