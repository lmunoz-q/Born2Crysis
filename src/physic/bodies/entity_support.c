#include <gjk.h>
#include <physic.h>

int		entity_support(t_vec3d *support, t_vec3d dir, void *data)
{
	t_entity	*e;
	int			i;
	double		d;
	int			mi;
	double		md;

	e = (t_entity*)data;
	mi = 0;
	md = vec3_dot(e->vertices[0], dir);
	i = 0;
	while (++i < 8)
	{
		d = vec3_dot(e->vertices[i], dir);
		if (d < md)
			continue;
		mi = i;
		md = d;
	}
	*support = e->vertices[mi];
	return (mi);
}

