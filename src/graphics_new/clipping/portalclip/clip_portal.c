/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:41:28 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 20:04:22 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static t_bool   is_right(double  p1[2], double p2[2], double c[2])
{
	t_bool res;

	res = (((p2[0] - p1[0]) * (c[1] - p1[1]) -
        (p2[1] - p1[1]) * (c[0] - p1[0])) > 0);
	return (res);
}

static t_vec2d     	line_intersect_2d(double a1[2], double a2[2], double b1[2], double b2[2])
{
    t_vec3d     p[2];
    t_vec2d     res;
    double      delta;

    p[0].y = a2[1] - a1[1];
    p[0].x = a1[0] - a2[0];
    p[0].z = p[0].y*a1[0] + p[0].x*a1[1];
    p[1].y = b2[1] - b1[1];
    p[1].x = b1[0] - b2[0];
    p[1].z = p[1].y*b1[0] + p[1].x*b1[1];
    delta = p[0].y*p[1].x - p[1].y*p[0].x;
    res.x = ((p[1].x*p[0].z) - (p[0].x*p[1].z))/delta;
    res.y = ((p[0].y*p[1].z) - (p[1].y*p[0].z))/delta;
    return (res);
}

static double	get_intersection_ratio(double a1[2], double a2[2], double b1[2], double b2[2])
{
	t_vec2d p;
	double	tmp[2];
	double	tmp2[2];
	double	res;

	p = line_intersect_2d(a1, a2, b1, b2);
	vec2vec2_substract(a2, a1, tmp);
	tmp2[0] = p.x - a1[0];
	tmp2[1] = p.y - a1[1];
	res = vec2_magnitude(tmp2) / vec2_magnitude(tmp);
	return (res);
}

static void	clip_2o1i(t_stack *outside, t_stack *inside, double edge[2][2])
{
	double ratio;
	
	ratio = get_intersection_ratio(((t_edge *)outside->data[0])->p, ((t_edge *)inside->data[0])->p, edge[0], edge[1]);
	((t_edge *)outside->data[0])->p[0] += (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[0])->p[0]) * ratio;
	((t_edge *)outside->data[0])->p[1] += (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[0])->p[1]) * ratio;
	((t_edge *)outside->data[0])->p[2] += (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[0])->p[2]) * ratio;
	((t_edge *)outside->data[0])->uv[0] += (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[0])->uv[0]) * ratio;
	((t_edge *)outside->data[0])->uv[1] += (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[0])->uv[1]) * ratio;
	((t_edge *)outside->data[0])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[0])->l[0]) * ratio;
	ratio = get_intersection_ratio(((t_edge *)outside->data[1])->p, ((t_edge *)inside->data[0])->p, edge[0], edge[1]);
	((t_edge *)outside->data[1])->p[0] += (((t_edge *)inside->data[0])->p[0] - ((t_edge *)outside->data[1])->p[0]) * ratio;
	((t_edge *)outside->data[1])->p[1] += (((t_edge *)inside->data[0])->p[1] - ((t_edge *)outside->data[1])->p[1]) * ratio;
	((t_edge *)outside->data[1])->p[2] += (((t_edge *)inside->data[0])->p[2] - ((t_edge *)outside->data[1])->p[2]) * ratio;
	((t_edge *)outside->data[1])->uv[0] += (((t_edge *)inside->data[0])->uv[0] - ((t_edge *)outside->data[1])->uv[0]) * ratio;
	((t_edge *)outside->data[1])->uv[1] += (((t_edge *)inside->data[0])->uv[1] - ((t_edge *)outside->data[1])->uv[1]) * ratio;
	((t_edge *)outside->data[1])->l[0] += (((t_edge *)inside->data[0])->l[0] - ((t_edge *)outside->data[1])->l[0]) * ratio;
}

void edge_to_polygon(t_edge *e, t_polygon *p, int i)
{
	p->v_light[i] = e->l[0];
	if (i == 0)
	{
		vec4_copy(p->v01, e->p);
		p->v01_uv[0] = e->uv[0];
		p->v01_uv[1] = e->uv[1];
	}
	if (i == 1)
	{
		vec4_copy(p->v12, e->p);
		p->v12_uv[0] = e->uv[0];
		p->v12_uv[1] = e->uv[1];
	}
	if (i == 2)
	{
		vec4_copy(p->v20, e->p);
		p->v20_uv[0] = e->uv[0];
		p->v20_uv[1] = e->uv[1];
	}
}

void	clip_1o2i(t_clipper *c, double edge[2][2], t_polygon *p, t_polygon *o)
{
	double		ratio;
	double		ratio2;

	ratio = get_intersection_ratio(((t_edge *)c->outside->data[0])->p, ((t_edge *)c->inside->data[0])->p, edge[0], edge[1]);
	ratio2 = get_intersection_ratio(((t_edge *)c->outside->data[0])->p, ((t_edge *)c->inside->data[1])->p, edge[0], edge[1]);
	o->v01[0] = ((t_edge *)c->outside->data[0])->p[0] + (((t_edge *)c->inside->data[0])->p[0] - ((t_edge *)c->outside->data[0])->p[0]) * ratio;
	o->v01[1] = ((t_edge *)c->outside->data[0])->p[1] + (((t_edge *)c->inside->data[0])->p[1] - ((t_edge *)c->outside->data[0])->p[1]) * ratio;
	o->v01[2] = ((t_edge *)c->outside->data[0])->p[2] + (((t_edge *)c->inside->data[0])->p[2] - ((t_edge *)c->outside->data[0])->p[2]) * ratio;
	o->v01_uv[0] = ((t_edge *)c->outside->data[0])->uv[0] + (((t_edge *)c->inside->data[0])->uv[0] - ((t_edge *)c->outside->data[0])->uv[0]) * ratio;
	o->v01_uv[1] = ((t_edge *)c->outside->data[0])->uv[1] + (((t_edge *)c->inside->data[0])->uv[1] - ((t_edge *)c->outside->data[0])->uv[1]) * ratio;
	o->v_light[0] = ((t_edge *)c->outside->data[0])->l[0] + (((t_edge *)c->inside->data[0])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio;
	o->v12[0] = ((t_edge *)c->outside->data[0])->p[0] + (((t_edge *)c->inside->data[1])->p[0] - ((t_edge *)c->outside->data[0])->p[0]) * ratio2;
	o->v12[1] = ((t_edge *)c->outside->data[0])->p[1] + (((t_edge *)c->inside->data[1])->p[1] - ((t_edge *)c->outside->data[0])->p[1]) * ratio2;
	o->v12[2] = ((t_edge *)c->outside->data[0])->p[2] + (((t_edge *)c->inside->data[1])->p[2] - ((t_edge *)c->outside->data[0])->p[2]) * ratio2;
	o->v12_uv[0] = ((t_edge *)c->outside->data[0])->uv[0] + (((t_edge *)c->inside->data[1])->uv[0] - ((t_edge *)c->outside->data[0])->uv[0]) * ratio2;
	o->v12_uv[1] = ((t_edge *)c->outside->data[0])->uv[1] + (((t_edge *)c->inside->data[1])->uv[1] - ((t_edge *)c->outside->data[0])->uv[1]) * ratio2;
	o->v_light[1] = ((t_edge *)c->outside->data[0])->l[0] + (((t_edge *)c->inside->data[1])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio2;
	o->tex_id = p->tex_id;
	edge_to_polygon(c->inside->data[0], o, 2);
	((t_edge *)c->outside->data[0])->p[0] += (((t_edge *)c->inside->data[1])->p[0] - ((t_edge *)c->outside->data[0])->p[0]) * ratio2;
	((t_edge *)c->outside->data[0])->p[1] += (((t_edge *)c->inside->data[1])->p[1] - ((t_edge *)c->outside->data[0])->p[1]) * ratio2;
	((t_edge *)c->outside->data[0])->p[2] += (((t_edge *)c->inside->data[1])->p[2] - ((t_edge *)c->outside->data[0])->p[2]) * ratio2;
	((t_edge *)c->outside->data[0])->uv[0] += (((t_edge *)c->inside->data[1])->uv[0] - ((t_edge *)c->outside->data[0])->uv[0]) * ratio2;
	((t_edge *)c->outside->data[0])->uv[1] += (((t_edge *)c->inside->data[1])->uv[1] - ((t_edge *)c->outside->data[0])->uv[1]) * ratio2;
	((t_edge *)c->outside->data[0])->l[0] += (((t_edge *)c->inside->data[1])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio2;
}

int		clip_polygon(t_polygon *p, int count, double edge[2][2])
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
		stack_push((is_right(edge[0], edge[1], p[i].v01) ? c->inside : c->outside), &point[0]);
		stack_push((is_right(edge[0], edge[1], p[i].v12) ? c->inside : c->outside), &point[1]);
		stack_push((is_right(edge[0], edge[1], p[i].v20) ? c->inside : c->outside), &point[2]);
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
	count = clip_polygon(p, count, (double [2][2]){{0 , height - 1}, {0, 0}});
	count = clip_polygon(p, count, (double [2][2]){{0 , 0}, {width - 1, 0}});
	count = clip_polygon(p, count, (double [2][2]){{width - 1, 0}, {width - 1, height - 1}});
	count = clip_polygon(p, count, (double [2][2]){{width - 1, height - 1}, {0, height - 1}});
	return (count);
}
