#include <gjk.h>

static inline int	gjk_muli_step_prevention(t_gjk_simplex *s)
{
	t_vec3d	pnt;
	double	denom;
	int		i;

	denom = 0.;
	i = -1;
	pnt = (t_vec3d){{}};
	while (++i < s->cnt)
		denom += s->bc.a[i];
	denom = 1.0 / denom;
	if (s->cnt == 1)
		pnt = s->v[0].p;
	else if (s->cnt == 2)
		pnt = vec3vec3_add(vec3scalar_multiply(s->v[0].p, denom * s->bc.a[0]),
							vec3scalar_multiply(s->v[1].p, denom * s->bc.a[1]));
	else if (s->cnt == 3)
		pnt = vec3vec3_add(vec3vec3_add(
							vec3scalar_multiply(s->v[0].p, denom * s->bc.a[0]),
							vec3scalar_multiply(s->v[1].p, denom * s->bc.a[1])),
							vec3scalar_multiply(s->v[2].p, denom * s->bc.a[2]));
	denom = vec3_dot(pnt, pnt);
	if (denom >= s->d)
		return (1);
	s->d = denom;
	return (0);
}

static inline void	gjk_new_direction(t_gjk_simplex *s, t_vec3d *dv)
{
	t_vec3d	a;

	if (s->cnt == 1)
		*dv = vec3scalar_multiply(s->v[0].p, -1.);
	else if (s->cnt == 2)
	{
		a = vec3vec3_substract(s->v[1].p, s->v[0].p);
		*dv = vec3vec3_crossproduct(vec3vec3_crossproduct(a,
									vec3scalar_multiply(s->v[1].p, -1.)), a);
	}
	else if (s->cnt == 3)
	{
		a = vec3vec3_crossproduct(vec3vec3_substract(s->v[1].p, s->v[0].p),
								vec3vec3_substract(s->v[2].p, s->v[0].p));
		if (vec3_dot(a, s->v[0].p) <= 0.0)
			*dv = a;
		else
			*dv = vec3scalar_multiply(a, -1);
	}
}

/*
** loop function, return 1 if further calculation is needed, 0 if end reached
*/

int gjk_loop(t_gjk_simplex *s, const t_gjk_support *sup, t_vec3d *dv)
{
	int				i;
	t_gjk_vertex	*vert;

	if (s == NULL || sup == NULL || dv == NULL
			|| (s->max_iter > 0 && s->iter >= s->max_iter))
		return (0);
	if (s->cnt == 0 && (s->d = __DBL_MAX__))
		s->max_iter = s->max_iter == 0 ? GJK_MAX_ITERATIONS : s->max_iter;
	i = -1;
	while (++i < s->cnt)
		if (!(sup->aid != s->v[i].aid || sup->bid != s->v[i].bid))
			return (0);
	vert = &s->v[s->cnt];
	vert->a = sup->a;
	vert->b = sup->b;
	vert->p = *dv;
	vert->aid = sup->aid;
	vert->bid = sup->bid;
	s->bc.a[s->cnt++] = 1.0;
	gjk_switch(s);
	if ((s->cnt == 4 && (s->hit = 1)) || gjk_muli_step_prevention(s))
		return (0);
	gjk_new_direction(s, dv);
	return (vec3_dot(*dv, *dv) >= GJK_EPSILON * GJK_EPSILON);
}
