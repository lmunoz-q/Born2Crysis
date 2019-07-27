/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_znear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:01:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 13:12:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		clip_1out2in(t_clipper *c, t_polygon *p, t_polygon *o)
{
	double		ratio;
	double		ratio2;

	ratio = ((t_edge *)c->outside->data[0])->dist / (((t_edge *)c->inside->data[0])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]);
	ratio2 = ((t_edge *)c->outside->data[0])->dist / (((t_edge *)c->inside->data[1])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]);
	o->v01.a[0] = ((t_edge *)c->outside->data[0])->p->a[0] + (((t_edge *)c->inside->data[0])->p->a[0] - ((t_edge *)c->outside->data[0])->p->a[0]) * ratio;
	o->v01.a[1] = ((t_edge *)c->outside->data[0])->p->a[1] + (((t_edge *)c->inside->data[0])->p->a[1] - ((t_edge *)c->outside->data[0])->p->a[1]) * ratio;
	o->v01.a[2] = ((t_edge *)c->outside->data[0])->p->a[2] + (((t_edge *)c->inside->data[0])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]) * ratio;
	o->v01_uv.a[0] = ((t_edge *)c->outside->data[0])->uv->a[0] + (((t_edge *)c->inside->data[0])->uv->a[0] - ((t_edge *)c->outside->data[0])->uv->a[0]) * ratio;
	o->v01_uv.a[1] = ((t_edge *)c->outside->data[0])->uv->a[1] + (((t_edge *)c->inside->data[0])->uv->a[1] - ((t_edge *)c->outside->data[0])->uv->a[1]) * ratio;
	o->v_light.a[0] = ((t_edge *)c->outside->data[0])->l[0] + (((t_edge *)c->inside->data[0])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio;
	o->v12.a[0] = ((t_edge *)c->outside->data[0])->p->a[0] + (((t_edge *)c->inside->data[1])->p->a[0] - ((t_edge *)c->outside->data[0])->p->a[0]) * ratio2;
	o->v12.a[1] = ((t_edge *)c->outside->data[0])->p->a[1] + (((t_edge *)c->inside->data[1])->p->a[1] - ((t_edge *)c->outside->data[0])->p->a[1]) * ratio2;
	o->v12.a[2] = ((t_edge *)c->outside->data[0])->p->a[2] + (((t_edge *)c->inside->data[1])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]) * ratio2;
	o->v12_uv.a[0] = ((t_edge *)c->outside->data[0])->uv->a[0] + (((t_edge *)c->inside->data[1])->uv->a[0] - ((t_edge *)c->outside->data[0])->uv->a[0]) * ratio2;
	o->v12_uv.a[1] = ((t_edge *)c->outside->data[0])->uv->a[1] + (((t_edge *)c->inside->data[1])->uv->a[1] - ((t_edge *)c->outside->data[0])->uv->a[1]) * ratio2;
	o->v_light.a[1] = ((t_edge *)c->outside->data[0])->l[0] + (((t_edge *)c->inside->data[1])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio2;
	o->tex_id = p->tex_id;
	o->transparency = p->transparency;
	edge_to_polygon(c->inside->data[0], o, 2);
	((t_edge *)c->outside->data[0])->p->a[0] += (((t_edge *)c->inside->data[1])->p->a[0] - ((t_edge *)c->outside->data[0])->p->a[0]) * ratio2;
	((t_edge *)c->outside->data[0])->p->a[1] += (((t_edge *)c->inside->data[1])->p->a[1] - ((t_edge *)c->outside->data[0])->p->a[1]) * ratio2;
	((t_edge *)c->outside->data[0])->p->a[2] += (((t_edge *)c->inside->data[1])->p->a[2] - ((t_edge *)c->outside->data[0])->p->a[2]) * ratio2;
	((t_edge *)c->outside->data[0])->uv->a[0] += (((t_edge *)c->inside->data[1])->uv->a[0] - ((t_edge *)c->outside->data[0])->uv->a[0]) * ratio2;
	((t_edge *)c->outside->data[0])->uv->a[1] += (((t_edge *)c->inside->data[1])->uv->a[1] - ((t_edge *)c->outside->data[0])->uv->a[1]) * ratio2;
	((t_edge *)c->outside->data[0])->l[0] += (((t_edge *)c->inside->data[1])->l[0] - ((t_edge *)c->outside->data[0])->l[0]) * ratio2;
}

static void	classify_points(t_edge *edges, t_clipper *c)
{
	edges[0].dist = ZNEAR - edges[0].p->a[2];
	edges[1].dist = ZNEAR - edges[1].p->a[2];
	edges[2].dist = ZNEAR - edges[2].p->a[2];
	stack_push((edges[0].p->a[2] >= ZNEAR) ? c->inside : c->outside, &edges[0]);
	stack_push((edges[1].p->a[2] >= ZNEAR) ? c->inside : c->outside, &edges[1]);
	stack_push((edges[2].p->a[2] >= ZNEAR) ? c->inside : c->outside, &edges[2]);
}

int			clip_znear(t_polygon *p, int count)
{
	int			i;
	t_clipper	*clip;
	t_edge		edge[3];
	int			newcount;
	
	newcount = count;
	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1 || !(clip = init_clipper()))
			continue ;
		init_edge(&p[i], edge);
		classify_points(edge, clip);
		if (clip->outside->top == 1)
			clip_2out1in_z(clip);
		if (clip->outside->top == 0)
			clip_1out2in(clip, &p[i], &p[newcount++]);
		if (clip->outside->top == 2)
			p[i].tex_id = -1;
	}
	return (newcount);
}
