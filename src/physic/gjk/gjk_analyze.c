#include <gjk.h>

static inline void	i_case_2(t_gjk_result *res,
							const t_gjk_simplex *s,
							double den)
{
	double as;
	double bs;

	as = den * s->bc.a[0];
	bs = den * s->bc.a[1];
	res->p0 = vec3vec3_add(vec3scalar_multiply(s->v[0].a, as),
							vec3scalar_multiply(s->v[1].a, bs));
	res->p1 = vec3vec3_add(vec3scalar_multiply(s->v[0].b, as),
							vec3scalar_multiply(s->v[1].b, bs));
}

static inline void	i_case_3(t_gjk_result *res,
							const t_gjk_simplex *s,
							double den)
{
	double as;
	double bs;
	double cs;

	as = den * s->bc.a[0];
	bs = den * s->bc.a[1];
	cs = den * s->bc.a[2];
	res->p0 = vec3vec3_add(vec3vec3_add(vec3scalar_multiply(s->v[0].a, as),
										vec3scalar_multiply(s->v[1].a, bs)),
										vec3scalar_multiply(s->v[2].a, cs));
	res->p1 = vec3vec3_add(vec3vec3_add(vec3scalar_multiply(s->v[0].b, as),
										vec3scalar_multiply(s->v[1].b, bs)),
										vec3scalar_multiply(s->v[2].b, cs));
}

static inline void	i_case_4(t_gjk_result *res,
							const t_gjk_simplex *s,
							double den)
{
	double	as;
	double	bs;
	double	cs;
	double	ds;

	as = den * s->bc.a[0];
	bs = den * s->bc.a[1];
	cs = den * s->bc.a[2];
	ds = den * s->bc.a[3];
	res->p0 = vec3vec3_add(
		vec3vec3_add(
			vec3scalar_multiply(s->v[0].a, as),
			vec3scalar_multiply(s->v[1].a, bs)),
		vec3vec3_add(
			vec3scalar_multiply(s->v[2].a, cs),
			vec3scalar_multiply(s->v[3].a, ds)));
	res->p1 = vec3vec3_add(
		vec3vec3_add(
			vec3scalar_multiply(s->v[0].b, as),
			vec3scalar_multiply(s->v[1].b, bs)),
		vec3vec3_add(
			vec3scalar_multiply(s->v[2].b, cs),
			vec3scalar_multiply(s->v[3].b, ds)));
}

/*
** populate res stgructure from the current simplex (usually the last calculated
** by gjk_loop)
** if the simplex is invalid, the content of res is not initialised
*/

void				gjk_analyze(t_gjk_result *res, const t_gjk_simplex *s)
{
	double		den;
	int			i;

	if (s->cnt < 1 || s->cnt > 4)
		return ;
	*res = (t_gjk_result){.iterations = s->iter, .hit = s->hit};
	den = 0;
	i = -1;
	while (++i < s->cnt)
		den += s->bc.a[i];
	den = 1.0f / den;
	if (s->cnt == 1)
	{
		res->p0 = s->v[0].a;
		res->p1 = s->v[0].b;
	}
	else if (s->cnt == 2)
		i_case_2(res, s, den);
	else if (s->cnt == 3)
		i_case_3(res, s, den);
	else
		i_case_4(res, s, den);
	if (res->hit == 0)
		res->distance_squared = vec3_dot(vec3vec3_substract(res->p1, res->p0),
			vec3vec3_substract(res->p1, res->p0));
}
