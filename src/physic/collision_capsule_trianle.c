#include <physic.h>

static inline int	project_point_triangle(t_vec3d *proj, t_vec3d pt,
											t_vec3d tri[3], t_vec3d normal)
{
	double	d;
	double	dots[3];

	d = vec3_dot(vec3vec3_substract(pt, tri[0]), normal);
	*proj = vec3vec3_substract(pt, vec3scalar_multiply(normal, d));
	dots[0] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(tri[1],
		tri[0]), normal), tri[0], *proj);
	dots[1] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(tri[2],
		tri[1]), normal), tri[1], *proj);
	dots[2] = dist_pointplane(vec3vec3_crossproduct(vec3vec3_substract(tri[0],
		tri[2]), normal), tri[2], *proj);
	*proj = vec3vec3_substract(pt, *proj);
	return (dots[0] <= 0.0 && dots[1] <= 0.0 && dots[2] <= 0.0);
}

int					collision_capsule_wall(t_vec3d *sep, t_vec3d cl[2],
											double r, t_wall w)
{
	t_vec3d	ssv[5];
	int		cnt;
	int		v;
	double	d;
	double	t;

	ssv[0] = ssv_seg_seg(cl[0], cl[1], w.vertices[0], w.vertices[1]);
	ssv[1] = ssv_seg_seg(cl[0], cl[1], w.vertices[1], w.vertices[2]);
	ssv[2] = ssv_seg_seg(cl[0], cl[1], w.vertices[2], w.vertices[0]);
	cnt = 3;
	cnt += project_point_triangle(&ssv[3], cl[0], w.vertices, w.normal);
	cnt += project_point_triangle(&ssv[cnt], cl[1], w.vertices, w.normal);
	d = __DBL_MAX__;
	v = 0;
	while (cnt--)
		if (d > (t = vec3_dot(ssv[cnt], ssv[cnt])))
		{
			v = cnt;
			d = t;
		}
	d = sqrt(d);
	if (d < r)
		*sep = vec3scalar_multiply(ssv[v], (r - d) / d);
	return (d < r);
}
