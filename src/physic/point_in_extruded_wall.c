#include <physic.h>

t_double3	d3_add(t_double3 a, t_double3 b)
{
	return ((t_double3){.x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z});
}

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

int	point_in_extruded_wall(t_double3 point, t_wall wall, t_wall_extrusion_data extrusion)
{
	t_double2	p;
	t_double2	w[3];
	t_double2	d;

	if (axis == 1) //X
	{
		point_in_triangle((t_double2){point.y, point.z}, (t_double2){wall[0].y, wall[0].z}, (t_double2){wall[1].y, wall[1].z}, (t_double2){wall[2].y, wall[2].z});
	}
	else if (axis == 2) //Y
	{
		point_in_triangle((t_double2){point.x, point.z}, (t_double2){wall[0].x, wall[0].z}, (t_double2){wall[1].x, wall[1].z}, (t_double2){wall[2].x, wall[2].z});
	}
	else //Z
	{
		point_in_triangle((t_double2){point.x, point.y}, (t_double2){wall[0].x, wall[0].y}, (t_double2){wall[1].x, wall[1].y}, (t_double2){wall[2].x, wall[2].y});
	}
}
