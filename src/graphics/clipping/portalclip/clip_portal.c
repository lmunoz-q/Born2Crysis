/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:41:28 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 13:07:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_bool	is_right(t_vec2d p1, t_vec2d p2, t_vec2d c)
{
	t_bool res;

	res = (((p2.n.x - p1.n.x) * (c.n.y - p1.n.y)
		- (p2.n.y - p1.n.y) * (c.n.x - p1.n.x)) > 0);
	return (res);
}

static t_vec2d	line_intersect_2d(t_vec2d a1, t_vec2d a2, t_vec2d b1, t_vec2d b2)
{
	t_vec3d	p[2];
	t_vec2d	res;
	double	delta;

	p[0].n.y = a2.a[1] - a1.a[1];
	p[0].n.x = a1.a[0] - a2.a[0];
	p[0].n.z = p[0].n.y * a1.a[0] + p[0].n.x * a1.a[1];
	p[1].n.y = b2.a[1] - b1.a[1];
	p[1].n.x = b1.a[0] - b2.a[0];
	p[1].n.z = p[1].n.y * b1.a[0] + p[1].n.x * b1.a[1];
	delta = p[0].n.y * p[1].n.x - p[1].n.y * p[0].n.x;
	res.n.x = ((p[1].n.x * p[0].n.z) - (p[0].n.x * p[1].n.z))/delta;
	res.n.y = ((p[0].n.y * p[1].n.z) - (p[1].n.y * p[0].n.z))/delta;
	return (res);
}

static double	get_intersection_ratio(t_vec2d a1, t_vec2d a2, t_vec2d b1, t_vec2d b2)
{
	t_vec2d	p;

	p = line_intersect_2d(a1, a2, b1, b2);
	return (vec2_magnitude(vec2vec2_substract(p, a1))
		/ vec2_magnitude(vec2vec2_substract(a2, a1)));
}

static void	clip_2o1i(t_stack *outside, t_stack *inside, t_vec2d edge[2])
{
	double ratio;

	ratio = get_intersection_ratio(((t_edge *)outside->data[0])->p->c2.vec2d, ((t_edge *)inside->data[0])->p->c2.vec2d, edge[0], edge[1]);
	((t_edge *)outside->data[0])->p->a[0] += (((t_edge *)inside->data[0])->p->a[0] - ((t_edge *)outside->data[0])->p->a[0]) * ratio;
	((t_edge *)outside->data[0])->p->a[1] += (((t_edge *)inside->data[0])->p->a[1] - ((t_edge *)outside->data[0])->p->a[1]) * ratio;
	((t_edge *)outside->data[0])->p->a[2] += (((t_edge *)inside->data[0])->p->a[2] - ((t_edge *)outside->data[0])->p->a[2]) * ratio;
	((t_edge *)outside->data[0])->uv->n.x += (((t_edge *)inside->data[0])->uv->n.x - ((t_edge *)outside->data[0])->uv->n.x) * ratio;
	((t_edge *)outside->data[0])->uv->n.y += (((t_edge *)inside->data[0])->uv->n.y - ((t_edge *)outside->data[0])->uv->n.y) * ratio;
	((t_edge *)outside->data[0])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio;
	ratio = get_intersection_ratio(((t_edge *)outside->data[1])->p->c2.vec2d, ((t_edge *)inside->data[0])->p->c2.vec2d, edge[0], edge[1]);
	((t_edge *)outside->data[1])->p->a[0] += (((t_edge *)inside->data[0])->p->a[0] - ((t_edge *)outside->data[1])->p->a[0]) * ratio;
	((t_edge *)outside->data[1])->p->a[1] += (((t_edge *)inside->data[0])->p->a[1] - ((t_edge *)outside->data[1])->p->a[1]) * ratio;
	((t_edge *)outside->data[1])->p->a[2] += (((t_edge *)inside->data[0])->p->a[2] - ((t_edge *)outside->data[1])->p->a[2]) * ratio;
	((t_edge *)outside->data[1])->uv->n.x += (((t_edge *)inside->data[0])->uv->n.x - ((t_edge *)outside->data[1])->uv->n.x) * ratio;
	((t_edge *)outside->data[1])->uv->n.y += (((t_edge *)inside->data[0])->uv->n.y - ((t_edge *)outside->data[1])->uv->n.y) * ratio;
	((t_edge *)outside->data[1])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[1])->l[0]) * ratio;
}

void	clip_1o2i(t_clipper *c, t_vec2d edge[2], t_polygon *p, t_polygon *o)
{
	double		ratio;
	double		ratio2;

	ratio = get_intersection_ratio(((t_edge *)c->outside->data[0])->p->c2.vec2d, ((t_edge *)c->inside->data[0])->p->c2.vec2d, edge[0], edge[1]);
	ratio2 = get_intersection_ratio(((t_edge *)c->outside->data[0])->p->c2.vec2d, ((t_edge *)c->inside->data[1])->p->c2.vec2d, edge[0], edge[1]);
	o->v01.a[0] = ((t_edge *)c->outside->data[0])->p->a[0] + (((t_edge *)c->inside->data[0])->p->a[0] - ((t_edge *)c->outside->data[0])->p->a[0]) * ratio;
	o->v01.a[1] = ((t_edge *)c->outside->data[0])->p->a[1] + (((t_edge *)c->inside->data[0])->p->a[1] - ((t_edge *)c->outside->data[0])->p->a[1]) * ratio;
	o->v01.a[2] = ((t_edge *)c->outside->data[0])->p->a[2] + (((t_edge *)c->inside->data[0])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]) * ratio;
	o->v01_uv.n.x = ((t_edge *)c->outside->data[0])->uv->n.x + (((t_edge *)c->inside->data[0])->uv->n.x - ((t_edge *)c->outside->data[0])->uv->n.x) * ratio;
	o->v01_uv.n.y = ((t_edge *)c->outside->data[0])->uv->n.y + (((t_edge *)c->inside->data[0])->uv->n.y - ((t_edge *)c->outside->data[0])->uv->n.y) * ratio;
	o->v_light.a[0] = ((t_edge *)c->outside->data[0])->l[0] + (((t_edge *)c->inside->data[0])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio;
	o->v12.a[0] = ((t_edge *)c->outside->data[0])->p->a[0] + (((t_edge *)c->inside->data[1])->p->a[0] - ((t_edge *)c->outside->data[0])->p->a[0]) * ratio2;
	o->v12.a[1] = ((t_edge *)c->outside->data[0])->p->a[1] + (((t_edge *)c->inside->data[1])->p->a[1] - ((t_edge *)c->outside->data[0])->p->a[1]) * ratio2;
	o->v12.a[2] = ((t_edge *)c->outside->data[0])->p->a[2] + (((t_edge *)c->inside->data[1])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]) * ratio2;
	o->v12_uv.n.x = ((t_edge *)c->outside->data[0])->uv->n.x + (((t_edge *)c->inside->data[1])->uv->n.x - ((t_edge *)c->outside->data[0])->uv->n.x) * ratio2;
	o->v12_uv.n.y = ((t_edge *)c->outside->data[0])->uv->n.y + (((t_edge *)c->inside->data[1])->uv->n.y - ((t_edge *)c->outside->data[0])->uv->n.y) * ratio2;
	o->v_light.a[1] = ((t_edge *)c->outside->data[0])->l[0] + (((t_edge *)c->inside->data[1])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio2;
	o->tex_id = p->tex_id;
	o->transparency = p->transparency;
	edge_to_polygon(c->inside->data[0], o, 2);
	((t_edge *)c->outside->data[0])->p->a[0] += (((t_edge *)c->inside->data[1])->p->a[0] - ((t_edge *)c->outside->data[0])->p->a[0]) * ratio2;
	((t_edge *)c->outside->data[0])->p->a[1] += (((t_edge *)c->inside->data[1])->p->a[1] - ((t_edge *)c->outside->data[0])->p->a[1]) * ratio2;
	((t_edge *)c->outside->data[0])->p->a[2] += (((t_edge *)c->inside->data[1])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]) * ratio2;
	((t_edge *)c->outside->data[0])->uv->n.x += (((t_edge *)c->inside->data[1])->uv->n.x - ((t_edge *)c->outside->data[0])->uv->n.x) * ratio2;
	((t_edge *)c->outside->data[0])->uv->n.y += (((t_edge *)c->inside->data[1])->uv->n.y - ((t_edge *)c->outside->data[0])->uv->n.y) * ratio2;
	((t_edge *)c->outside->data[0])->l[0] += (((t_edge *)c->inside->data[1])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio2;
}

int		clip_polygon(t_polygon *p, int count, t_vec2d edge[2])
{
	t_edge		point[3];
	int			newcount;
	t_clipper	*c;
	int			i;

	newcount = count;
	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1 || !(c = init_clipper()))
			continue ;
		init_edge(&p[i], point);
		stack_push((is_right(edge[0], edge[1], p[i].v01.c2.vec2d) ? c->inside : c->outside), &point[0]);
		stack_push((is_right(edge[0], edge[1], p[i].v12.c2.vec2d) ? c->inside : c->outside), &point[1]);
		stack_push((is_right(edge[0], edge[1], p[i].v20.c2.vec2d) ? c->inside : c->outside), &point[2]);
		if (c->outside->top == 2)
			p[i].tex_id = -1;
		if (c->outside->top == 1)
			clip_2o1i(c->outside, c->inside, edge);
		if (c->outside->top == 0)
			clip_1o2i(c, edge, &p[i], &p[newcount++]);
	}
	return (newcount);
}

int			portal_clip(t_polygon *p, int count, int width, int height)
{
	count = clip_polygon(p, count, (t_vec2d [2]){{.a = {0 , height + 1}}, {.a = {0, 0}}});
	count = clip_polygon(p, count, (t_vec2d [2]){{.a = {0 , 0}}, {.a = {width + 1, 0}}});
	count = clip_polygon(p, count, (t_vec2d [2]){{.a = {width + 1, 0}}, {.a = {width + 1, height + 1}}});
	count = clip_polygon(p, count, (t_vec2d [2]){{.a = {width + 1, height + 1}}, {.a = {0, height + 1}}});
	return (count);
}
