#include <gjk.h>

static inline int	i_3(t_gjk_simplex *s, t_vec3d v3[12], double d[30])
{
	if (d[19] <= 0. && d[15] <= 0. && d[8] > 0. && d[9] > 0.)
	{
		s->v[0] = s->v[3];
		s->v[1] = s->v[2];
		s->bc.a[0] = d[8];
		s->bc.a[1] = d[9];
		return (1);
	}
	if (d[16] <= 0. && d[14] <= 0. && d[10] > 0. && d[11] > 0.)
	{
		s->v[1] = s->v[3];
		s->bc.a[0] = d[10];
		s->bc.a[1] = d[11];
		return (1);
	}
	if (d[18] <= 0. && d[12] <= 0. && d[6] > 0. && d[7] > 0.)
	{
		s->v[0] = s->v[1];
		s->v[1] = s->v[3];
		s->bc.a[0] = d[6];
		s->bc.a[1] = d[7];
		return (1);
	}
	return (case_4_bis(s, v3, d));
}

static inline int	i_2(t_gjk_simplex *s, t_vec3d v3[12], double d[30])
{
	if (d[23] <= 0. && d[13] <= 0. && d[0] > 0. && d[1] > 0.)
	{
		s->bc.a[0] = d[0];
		s->bc.a[1] = d[1];
		return (1);
	}
	if (d[21] <= 0. && d[20] <= 0. && d[2] > 0. && d[3] > 0.)
	{
		s->v[0] = s->v[1];
		s->v[1] = s->v[2];
		s->bc.a[0] = d[2];
		s->bc.a[1] = d[3];
		return (1);
	}
	if (d[22] <= 0. && d[17] <= 0. && d[4] > 0. && d[5] > 0.)
	{
		s->v[1] = s->v[0];
		s->v[0] = s->v[2];
		s->bc.a[0] = d[4];
		s->bc.a[1] = d[5];
		return (1);
	}
	return (i_3(s, v3, d));
}

static inline int	i_1(t_gjk_simplex *s, t_vec3d v3[12], double d[30])
{
	d[14] = vec3_dot(v3[11], v3[8]);
	v3[8] = vec3vec3_crossproduct(v3[4], v3[7]);
	v3[9] = vec3vec3_crossproduct(s->v[2].p, s->v[3].p);
	v3[10] = vec3vec3_crossproduct(s->v[3].p, s->v[0].p);
	v3[11] = vec3vec3_crossproduct(s->v[0].p, s->v[2].p);
	d[15] = vec3_dot(v3[9], v3[8]);
	d[16] = vec3_dot(v3[10], v3[8]);
	d[17] = vec3_dot(v3[11], v3[8]);
	v3[8] = vec3vec3_crossproduct(v3[2], v3[6]);
	v3[9] = vec3vec3_crossproduct(s->v[1].p, s->v[3].p);
	v3[10] = vec3vec3_crossproduct(s->v[3].p, s->v[2].p);
	v3[11] = vec3vec3_crossproduct(s->v[2].p, s->v[1].p);
	d[18] = vec3_dot(v3[9], v3[8]);
	d[19] = vec3_dot(v3[10], v3[8]);
	d[20] = vec3_dot(v3[11], v3[8]);
	v3[8] = vec3vec3_crossproduct(v3[1], v3[4]);
	v3[9] = vec3vec3_crossproduct(s->v[1].p, s->v[2].p);
	v3[10] = vec3vec3_crossproduct(s->v[2].p, s->v[0].p);
	v3[11] = vec3vec3_crossproduct(s->v[0].p, s->v[1].p);
	d[21] = vec3_dot(v3[9], v3[8]);
	d[22] = vec3_dot(v3[10], v3[8]);
	d[23] = vec3_dot(v3[11], v3[8]);
	s->cnt = 2;
	return (i_2(s, v3, d));
}

static inline int	i_0(t_gjk_simplex *s, t_vec3d v3[12], double d[30])
{
	s->cnt = 1;
	if (d[1] <= 0. && d[4] <= 0. && d[11] <= 0.)
		return (1);
	if (d[0] <= 0. && d[3] <= 0. && d[7] <= 0.)
	{
		s->v[0] = s->v[1];
		return (1);
	}
	if (d[2] <= 0. && d[5] <= 0. && d[8] <= 0.)
	{
		s->v[0] = s->v[2];
		return (1);
	}
	if (d[6] <= 0. && d[9] <= 0. && d[10] <= 0.)
	{
		s->v[0] = s->v[3];
		return (1);
	}
	v3[8] = vec3vec3_crossproduct(v3[7], v3[1]);
	v3[9] = vec3vec3_crossproduct(s->v[3].p, s->v[1].p);
	v3[10] = vec3vec3_crossproduct(s->v[1].p, s->v[0].p);
	v3[11] = vec3vec3_crossproduct(s->v[0].p, s->v[3].p);
	d[12] = vec3_dot(v3[9], v3[8]);
	d[13] = vec3_dot(v3[10], v3[8]);
	return (i_1(s, v3, d));
}

inline int	case_4(t_gjk_simplex *s)
{
	t_vec3d	v3[12];
	double	d[30];

	v3[0] = vec3vec3_substract(s->v[0].p, s->v[1].p);
	v3[1] = vec3vec3_substract(s->v[1].p, s->v[0].p);
	v3[2] = vec3vec3_substract(s->v[1].p, s->v[2].p);
	v3[3] = vec3vec3_substract(s->v[2].p, s->v[1].p);
	v3[4] = vec3vec3_substract(s->v[2].p, s->v[0].p);
	v3[5] = vec3vec3_substract(s->v[3].p, s->v[1].p);
	v3[6] = vec3vec3_substract(s->v[3].p, s->v[2].p);
	v3[7] = vec3vec3_substract(s->v[3].p, s->v[0].p);
	d[0] = vec3_dot(s->v[1].p, v3[1]);
	d[1] = vec3_dot(s->v[0].p, v3[0]);
	d[2] = vec3_dot(s->v[2].p, v3[3]);
	d[3] = vec3_dot(s->v[1].p, v3[2]);
	d[4] = vec3_dot(s->v[0].p, vec3vec3_substract(s->v[0].p, s->v[2].p));
	d[5] = vec3_dot(s->v[2].p, v3[4]);
	d[6] = vec3_dot(s->v[3].p, v3[5]);
	d[7] = vec3_dot(s->v[1].p, vec3vec3_substract(s->v[1].p, s->v[3].p));
	d[8] = vec3_dot(s->v[2].p, vec3vec3_substract(s->v[2].p, s->v[3].p));
	d[9] = vec3_dot(s->v[3].p, v3[6]);
	d[10] = vec3_dot(s->v[3].p, v3[7]);
	d[11] = vec3_dot(s->v[0].p, vec3vec3_substract(s->v[0].p, s->v[3].p));
	s->bc.a[0] = 1.;
	return (i_0(s, v3, d));
}
