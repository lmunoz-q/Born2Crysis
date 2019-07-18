#include <physic.h>

int	point_in_triangle(t_double2 s, t_double2 a, t_double2 b, t_double2 c)
{
	double	as_x;
	double	as_y;
	int		s_ab;

	as_y = s.y - a.y;
	as_x = s.x - a.x;
	s_ab = (b.x - a.x) * as_y - (b.y - a.y) * as_x > 0;
	return (!((c.x - a.x) * as_y - (c.y - a.y) * as_x > 0 == s_ab
		|| (c.x - b.x) * (s.y - b.y) - (c.y - b.y) * (s.x - b.x) > 0 != s_ab));
}

int	small_hack(t_double2 p, t_double2 d, t_double2 a, t_double2 b)
{
	t_double2	pp;
	t_double2	bp;

	pp = d2_substract(p, a);
	bp = d2_substract(b,a);
	return ((d2_dot_product(bp, pp) >= 0.0)
		!= (d2_dot_product(bp, d2_add(pp, d)) >= 0.0));
}

//projection of point P on plane with normal N and a point O
//p' = p - (n ⋅ (p - o)) * n

// int	point_in_extruded_wall(t_double3 point, t_wall wall, t_wall_extrusion_data extrusion)
// {
// 	t_double2	p;
// 	t_double2	w[3];
// 	t_double2	d;
//
// 	if (axis == 1) //X
// 	{
// 		point_in_triangle((t_double2){point.y, point.z}, (t_double2){wall[0].y, wall[0].z}, (t_double2){wall[1].y, wall[1].z}, (t_double2){wall[2].y, wall[2].z});
// 	}
// 	else if (axis == 2) //Y
// 	{
// 		point_in_triangle((t_double2){point.x, point.z}, (t_double2){wall[0].x, wall[0].z}, (t_double2){wall[1].x, wall[1].z}, (t_double2){wall[2].x, wall[2].z});
// 	}
// 	else //Z
// 	{
// 		point_in_triangle((t_double2){point.x, point.y}, (t_double2){wall[0].x, wall[0].y}, (t_double2){wall[1].x, wall[1].y}, (t_double2){wall[2].x, wall[2].y});
// 	}
// }

/*
** extrusion: x: size of the extrusion, Y: delta multiplicator of Y orientation
*/

int	point_in_extruded_wall(t_double3 point, t_wall wall, t_double2 extrusion, double *correction)
{
	t_double3	v;
	double		d;
	t_double3	p;
	double		dots[3];
	double		y;

	printf("point: %f %f %f\n", point.x, point.y, point.z);
	v = d3_substract(point, wall.center);
	y = d3_dot_product((t_double3){0, 1, 0}, wall.normal);
	printf("y det (1 floor, 0 wall, -1 ceiling): %f\n", y);
	d = d3_dot_product(v, wall.normal);
	printf("det: %f\n", d);
	p = d3_substract(point, d3_scale(wall.normal, d));
	printf("projection: %f %f %f\n", p.x, p.y, p.z);
	dots[0] = d3_dot_product(d3_substract(p, wall.vertices[0]), d3_substract(wall.vertices[1], wall.vertices[0]));
	dots[1] = d3_dot_product(d3_substract(p, wall.vertices[1]), d3_substract(wall.vertices[2], wall.vertices[1]));
	dots[2] = d3_dot_product(d3_substract(p, wall.vertices[2]), d3_substract(wall.vertices[0], wall.vertices[2]));
	printf("dots: %f %f %f\n", dots[0], dots[1], dots[2]);
	if ((dots[0] > 0.0 || dots[1] > 0.0 || dots[2] > 0.0)
			&& (dots[0] < 0.0 || dots[1] < 0.0 || dots[2] < 0.0))
		return (0);
	printf("in triangle\n");
	double md = (d < 0.0 ? -1.0 : 1.0) * d3_magnitude(d3_substract(p, point));
	printf("magnitude * direction of p->p' %f\n", md);
	double ec = /*(1.0 - fabs(y)) * */extrusion.y;
	printf("extrusion correction: %f\n", ec);
	printf("positive extrusion (in front of the wall): %f\n", ec);
	printf("negative extrusion (behind the wall): %f\n", extrusion.x - ec);
	if (md < ec && md > -(extrusion.x - ec))
		printf("in extrusion\n");
	else
		return (0);
	printf("correction multiplicator: %f\n", ec - md);
	if (correction != NULL)
		*correction = ec - md;
	return (1);
}
