#include <gjk.h>
#include <physic.h>

/*
** data is a pointer to a t_wall
*/

int		wall_support(t_vec3d *support, t_vec3d dir, void *data)
{
	t_wall	*w;
	int		i;
	double	d;
	int		mi;
	double	md;

	w = (t_wall*)data;
	mi = 0;
	md = vec3_dot(w->vertices[0], dir);
	i = 0;
	while (++i < 3)
	{
		d = vec3_dot(w->vertices[i], dir);
		if (d < md)
			continue;
		mi = i;
		md = d;
	}
	*support = w->vertices[mi];
	return (mi);
}
