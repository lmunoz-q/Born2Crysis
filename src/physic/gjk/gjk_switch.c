#include <gjk.h>

static inline int	i_case_3_1(t_gjk_simplex *s, double d[9], t_vec3d c)
{
	d[6] = vec3_dot(vec3vec3_crossproduct(s->v[1].p, s->v[2].p), c);
	d[7] = vec3_dot(vec3vec3_crossproduct(s->v[2].p, s->v[0].p), c);
	d[8] = vec3_dot(vec3vec3_crossproduct(s->v[0].p, s->v[1].p), c);
	if (d[0] > 0. && d[1] > 0. && d[8] <= 0.)
	{
		s->bc = (t_vec4d){{d[0], d[1], 0., 0.}};
		return (1);
	}
	if (d[2] > 0. && d[3] > 0. && d[6] <= 0.)
	{
		s->v[0] = s->v[1];
		s->v[1] = s->v[2];
		s->bc = (t_vec4d){{d[2], d[3], 0., 0.}};
		return (1);
	}
	if (d[4] > 0. && d[5] > 0. && d[7] <= 0.)
	{
		s->v[1] = s->v[0];
		s->v[0] = s->v[2];
		s->bc = (t_vec4d){{d[4], d[5], 0., 0.}};
		return (1);
	}
	s->bc = (t_vec4d){{d[6], d[7], d[8], 0.}};
	s->cnt = 3;
	return (0);
}

static inline int	i_case_3_0(t_gjk_simplex *s)
{
	double	d[9];

	d[0] = vec3_dot(s->v[1].p, vec3vec3_substract(s->v[1].p, s->v[0].p));
	d[1] = vec3_dot(s->v[0].p, vec3vec3_substract(s->v[0].p, s->v[1].p));
	d[2] = vec3_dot(s->v[2].p, vec3vec3_substract(s->v[2].p, s->v[1].p));
	d[3] = vec3_dot(s->v[1].p, vec3vec3_substract(s->v[1].p, s->v[2].p));
	d[4] = vec3_dot(s->v[0].p, vec3vec3_substract(s->v[0].p, s->v[2].p));
	d[5] = vec3_dot(s->v[2].p, vec3vec3_substract(s->v[2].p, s->v[0].p));
	s->cnt = 1;
	s->bc.a[0] = 1.;
	if (d[1] <= 0. && d[4] <= 0.)
		return (1);
	if (d[0] <= 0. && d[3] <= 0.)
	{
		s->v[0] = s->v[1];
		return (1);
	}
	if (d[2] <= 0. && d[5] <= 0.)
	{
		s->v[0] = s->v[2];
		return (1);
	}
	s->cnt = 2;
	return (i_case_3_1(s, d, vec3vec3_crossproduct(vec3vec3_substract(
		s->v[1].p, s->v[0].p), vec3vec3_substract(s->v[2].p, s->v[0].p))));
}

inline void			gjk_switch(t_gjk_simplex *s)
{
	double	u;
	double	v;

	if (s->cnt == 2)
	{
		u = vec3_dot(s->v[1].p, vec3vec3_substract(s->v[1].p, s->v[0].p));
		v = vec3_dot(s->v[0].p, vec3vec3_substract(s->v[0].p, s->v[1].p));
		if (v <= 0. || u <= 0.)
		{
			if (u <= 0.)
				s->v[0] = s->v[1];
			s->bc.a[0] = 1.;
			s->cnt = 1;
			return ;
		}
		s->bc.a[0] = u;
		s->bc.a[1] = v;
		s->cnt = 2;
	}
	else if (s->cnt == 3 && i_case_3_0(s))
		return ;
	else if (s->cnt == 4)
		case_4(s);
}
