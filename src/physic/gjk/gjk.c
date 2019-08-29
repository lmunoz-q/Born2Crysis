#include <gjk.h>

t_gjk_result	gjk(t_gjk_body a, t_gjk_body b)
{
	t_vec3d			d;
	t_gjk_support	sup;
	t_gjk_simplex	simp;
	t_gjk_result	res;

	simp = (t_gjk_simplex){};
	if (!a.direction(&d, a.data))
	{
		if (b.direction(&d, b.data))
			d = vec3scalar_multiply(d, -1.);
		else
			d = (t_vec3d){{0., -1., 0.}};
	}
	a.support(&sup.a, d, a.data);
	b.support(&sup.b, vec3scalar_multiply(d, -1.), b.data);
	while (gjk_loop(&simp, &sup, &d))
	{
		a.support(&sup.a, d, a.data);
		b.support(&sup.b, vec3scalar_multiply(d, -1.), b.data);
		d = vec3vec3_substract(sup.b, sup.a);
	}
	res = (t_gjk_result){};
	gjk_analyze(&res, &simp);
	return (res);
}
