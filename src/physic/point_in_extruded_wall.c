#include <physic.h>
#include <stdio.h>

/*
**	y = 180.0 / M_PI * acos(y);
**	if (y < 30.0)
**		return (1);
**	if (y < 60.0)
**		return (2);
**	if (y < 90.0)
**		return (3);
**	if (y < 100.0)
**		return (4);
**	return (5);
**
** 		d = (d - t) * continuous; //ugly fix for btp in extreme ramp condition
*/

double	line_plane_intersection(t_vec3d normal, t_vec3d p0, t_vec3d line,
	t_vec3d l0)
{
	return (vec3_dot(vec3vec3_substract(p0, l0), normal) / vec3_dot(normal,
		line));
//	return ((vec3_dot(normal, p0) + vec3_dot(normal, l0)) / vec3_dot(normal, line));
}

double	entity_wall_collision(t_entity original, t_entity ent, t_wall wall,
	double *correction)
{
	double	d;
	t_vec3d	p;
	double	dots[3];
	double	y;
	double	ec;
	double	continuous;
	t_vec3d	l;

	y = vec3_dot((t_vec3d){.a = {0, 1, 0}}, wall.normal);
	ec = (1.0 - fabs(y)) * ent.radius;
	// if (ent.radius < 1.0)
	// 	ent.radius = 1.0;
	if (y < 0.0)
	{
		ent.position.n.y += ent.height;
		original.position.n.y += original.height;
	}
	d = vec3_dot(vec3vec3_substract(ent.position, wall.center), wall.normal);
//	double t = vec3_dot(vec3vec3_substract(original.position, wall.center),
//		wall.normal);
//	if (ec - t > ec - d)
//		return (-42);
	l = /*vec3_normalize(*/vec3vec3_substract(ent.position, original.position)/*)*/;
	continuous = line_plane_intersection(wall.normal, wall.center, l, original.position);
	if (continuous < INFINITY && continuous > -INFINITY)
		printf("continuous: %f\n", continuous);
	if (continuous > 0.0 && continuous <= 1.0)
	{
//		printf("warning (%f): %f %f %f, %f %f %f\n", continuous, original.position.n.x, original.position.n.y, original.position.n.z, ent.position.n.x, ent.position.n.y, ent.position.n.z);
		p = vec3vec3_add(original.position, vec3scalar_multiply(l, continuous));
//		t = vec3_dot(vec3vec3_substract(p, wall.center), wall.normal);
//		p = vec3vec3_substract(ent.position, vec3scalar_multiply(wall.normal, d));
//		printf("p: %f %f %f\n", p.n.x, p.n.y, p.n.z);
//		printf("normal: %f %f %f\n", wall.normal.n.x, wall.normal.n.y, wall.normal.n.z);
//		printf("wall: %f %f %f, %f %f %f, %f %f %f\n", wall.vertices[0].n.x, wall.vertices[0].n.y, wall.vertices[0].n.z, wall.vertices[1].n.x, wall.vertices[1].n.y, wall.vertices[1].n.z, wall.vertices[2].n.x, wall.vertices[2].n.y, wall.vertices[2].n.z);
		dots[0] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.
			vertices[1], wall.vertices[0]), wall.normal), wall.vertices[0], p);
		dots[1] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.
			vertices[2], wall.vertices[1]), wall.normal),wall.vertices[1], p);
		dots[2] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.
			vertices[0], wall.vertices[2]), wall.normal), wall.vertices[2], p);
//		printf("dots: %f %f %f\n", dots[0], dots[1], dots[2]);
		if (!((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
			&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0)))
		{
//			printf("original d: %f\n", d);
//			d = (d - t) * continuous;
//			printf("new collision distance: %f\n", d);
			continuous = 0.42;
		}
	}
	if (continuous != 0.42)
	{
		p = vec3vec3_substract(ent.position, vec3scalar_multiply(wall.normal, d));
		dots[0] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[1], wall.vertices[0]), wall.normal), wall.vertices[0], p);
		dots[1] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[2], wall.vertices[1]), wall.normal), wall.vertices[1], p);
		dots[2] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(wall.vertices[0], wall.vertices[2]), wall.normal), wall.vertices[2], p);
		if ((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
			&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0))
			return (-42);
		if (d > ec || d <= -(ent.radius * 10.0 * vec3_magnitude(ent.velocity) - ec))
			return (-42);
	}
	if (correction != NULL)
		*correction = ec - d;
	return (y);
}
