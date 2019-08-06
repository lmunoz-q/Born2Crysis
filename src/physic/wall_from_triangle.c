#include <physic.h>

t_wall	wall_from_triangle(t_vec3d triangle[3]) //clock-wise notation
{
	t_wall	out = {};
	//double	t;
	//double	msd;
	//int		i;

	(void)triangle;
	//out.vertices[0] = triangle[0];
	//out.vertices[1] = triangle[1];
	//out.vertices[2] = triangle[2];
	//out.normal = d3_normalize(d3_cross_product(
	//	d3_substract(triangle[1], triangle[0]),
	//	d3_substract(triangle[2], triangle[0])));
	//out.center = d3_scale(
	//	d3_add(d3_add(triangle[0], triangle[1]), triangle[2]), 1.0 / 3.0);
	//msd = 0.0;
	//i = -1;
	//while (++i < 3)
	//{
	//	t = d3_squared_magnitude(d3_substract(triangle[i], out.center));
	//	if (t > msd)
	//		msd = t;
	//}
	//out.radius = sqrt(msd);
	return (out);
}
