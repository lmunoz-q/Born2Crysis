#include <physic.h>

/*
** extrusion: x: size of the extrusion, displacement (along the normal) of the extrusion
*/

int	point_in_extruded_wall(t_vec3d point, t_wall wall, t_vec2d extrusion, double *correction)
{
	t_vec3d		v;
	double		d;
	t_vec3d		p;
	double		dots[3];
//	double		y;

//	printf("point: %f %f %f\n", point.n.x, point.n.y, point.n.z);
//	printf("wall center: %f %f %f\n", wall.center.n.x, wall.center.n.y, wall.center.n.z);
	v = vec3vec3_substract(point, wall.center);
//	printf("v: %f %f %f\n", v.n.x, v.n.y, v.n.z);
//	y = vec3_dot((t_vec3d){.a = {0, 1, 0}}, wall.normal);
//	printf("y det (1 floor, 0 wall, -1 ceiling): %f\n", y);
	d = vec3_dot(v, wall.normal);
//	printf("det: %f\n", d);
	p = vec3vec3_substract(point, vec3scalar_multiply(wall.normal, d));
//	printf("projection: %f %f %f\n", p.n.x, p.n.y, p.n.z);
	dots[0] = vec3_dot(vec3vec3_substract(p, wall.vertices[0]), vec3vec3_substract(wall.vertices[1], wall.vertices[0]));
	dots[1] = vec3_dot(vec3vec3_substract(p, wall.vertices[1]), vec3vec3_substract(wall.vertices[2], wall.vertices[1]));
	dots[2] = vec3_dot(vec3vec3_substract(p, wall.vertices[2]), vec3vec3_substract(wall.vertices[0], wall.vertices[2]));
//	 printf("dots: %f %f %f\n", dots[0], dots[1], dots[2]);
	if ((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
			&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0))
		return (0);
//	printf("in triangle\n");
	double md = (d < 0.0 ? -1.0 : 1.0) * vec3_magnitude(vec3vec3_substract(p, point));
//	printf("magnitude * direction of p->p' %f\n", md);
	double ec = //(1.0 - fabs(y)) *
		extrusion.n.y;
//	printf("extrusion correction: %f\n", ec);
//	printf("positive extrusion (in front of the wall): %f\n", ec);
//	printf("negative extrusion (behind the wall): %f\n", extrusion.n.x - ec);
	if (md < ec && md > -(extrusion.n.x - ec))
;//		printf("in extrusion\n");
	else
		return (0);
//	printf("correction multiplicator: %f\n", ec - md);
	if (correction != NULL)
		*correction = ec - md;
	return (1);
}
