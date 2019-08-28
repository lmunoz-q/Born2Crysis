#include <gjk.h>

static inline double	f3box(const t_vec3d a, const t_vec3d b, const t_vec3d c)
{
	return (vec3_dot(vec3vec3_crossproduct(a, b), c));
}

static inline int		i_0(t_gjk_simplex *s, double d[30])
{
	if (d[27] <= 0. && d[15] > 0. && d[16] > 0. && d[17] > 0.)
	{
		s->v[1] = s->v[2];
		s->v[2] = s->v[3];
		s->bc.a[0] = d[15];
		s->bc.a[1] = d[16];
		s->bc.a[2] = d[17];
		return (1);
	}
	if (d[28] <= 0. && d[12] > 0. && d[13] > 0. && d[14] > 0.)
	{
		s->v[2] = s->v[1];
		s->v[1] = s->v[3];
		s->bc.a[0] = d[12];
		s->bc.a[1] = d[13];
		s->bc.a[2] = d[14];
		return (1);
	}
	s->bc.a[0] = d[26];
	s->bc.a[1] = d[27];
	s->bc.a[2] = d[28];
	s->bc.a[3] = d[29];
	s->cnt = 4;
	return (0);
}

inline int				case_4_bis(t_gjk_simplex *s, t_vec3d v3[12],
									double d[30])
{
	d[24] = f3box(v3[3], v3[0], v3[5]);
	d[25] = (d[24] == 0) ? 1.: 1. / d[24];
	d[26] = f3box(s->v[2].p, s->v[3].p, s->v[1].p) * d[25];
	d[27] = f3box(s->v[2].p, s->v[0].p, s->v[3].p) * d[25];
	d[28] = f3box(s->v[3].p, s->v[0].p, s->v[1].p) * d[25];
	d[29] = f3box(s->v[1].p, s->v[0].p, s->v[2].p) * d[25];
	s->cnt = 3;
	if (d[29] <= 0. && d[21] > 0. && d[22] > 0. && d[23] > 0.)
	{
		s->bc.a[0] = d[21];
		s->bc.a[1] = d[22];
		s->bc.a[2] = d[23];
		return (1);
	}
	if (d[26] <= 0. && d[18] > 0. && d[19] > 0. && d[20] > 0.)
	{
		s->v[0] = s->v[2];
		s->v[2] = s->v[3];
		s->bc.a[0] = d[18];
		s->bc.a[1] = d[19];
		s->bc.a[2] = d[20];
		return (1);
	}
	return (i_0(s, d));
}
