#include <physic.h>

t_wall	wall_from_triangle(t_vec3d triangle[3]) //clock-wise notation
{
	t_wall	out;
	double	t;
	double	msd;
	int		i;
	t_vec3d	tmp;

	out.vertices[0] = triangle[0];
	out.vertices[1] = triangle[1];
	out.vertices[2] = triangle[2];
	out.normal = vec3_normalize(vec3vec3_crossproduct(
		vec3vec3_substract(triangle[1], triangle[0]),
		vec3vec3_substract(triangle[2], triangle[0])));
//	printf("normal of triangle: %f %f %f\n", out.normal.n.x, out.normal.n.y, out.normal.n.z);
	out.center = vec3scalar_multiply(vec3vec3_add(
		vec3vec3_add(triangle[0], triangle[1]), triangle[2]), 1.0 / 3.0);
//	printf("center of triangle: %f %f %f\n", out.center.n.x, out.center.n.y, out.center.n.z);
	msd = 0.0;
	i = -1;
	while (++i < 3)
	{
		tmp = vec3vec3_substract(triangle[i], out.center);
		t = vec3_dot(tmp, tmp); //square of magnitude
		if (t > msd)
			msd = t;
	}
	out.radius = sqrt(msd);
	out.friction = 1.0;
	out.on_contact_trigger = 0;
//	printf("radius of triangle: %f\n", out.radius);
	return (out);
}
