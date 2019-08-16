/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_1o2i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:24:07 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/15 19:24:23 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		r_clip_1o2i(t_clipper *c, t_polygon *o, double ratio)
{
	o->v01.a[0] = ((t_edge *)c->out->data[0])->p->a[0]
		+ (((t_edge *)c->in->data[0])->p->a[0]
		- ((t_edge *)c->out->data[0])->p->a[0]) * ratio;
	o->v01.a[1] = ((t_edge *)c->out->data[0])->p->a[1]
		+ (((t_edge *)c->in->data[0])->p->a[1]
		- ((t_edge *)c->out->data[0])->p->a[1]) * ratio;
	o->v01.a[2] = ((t_edge *)c->out->data[0])->p->a[2]
		+ (((t_edge *)c->in->data[0])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]) * ratio;
	o->v01_uv.n.x = ((t_edge *)c->out->data[0])->uv->n.x
		+ (((t_edge *)c->in->data[0])->uv->n.x
		- ((t_edge *)c->out->data[0])->uv->n.x) * ratio;
	o->v01_uv.n.y = ((t_edge *)c->out->data[0])->uv->n.y
		+ (((t_edge *)c->in->data[0])->uv->n.y
		- ((t_edge *)c->out->data[0])->uv->n.y) * ratio;
	o->v_light.a[0] = ((t_edge *)c->out->data[0])->l[0]
		+ (((t_edge *)c->in->data[0])->l[0]
		- ((t_edge *)c->out->data[0])->l[0]) * ratio;
}

void		r2_clip_1o2i(t_clipper *c, t_polygon *o, double ratio2)
{
	o->v12.a[0] = ((t_edge *)c->out->data[0])->p->a[0]
		+ (((t_edge *)c->in->data[1])->p->a[0]
		- ((t_edge *)c->out->data[0])->p->a[0]) * ratio2;
	o->v12.a[1] = ((t_edge *)c->out->data[0])->p->a[1]
		+ (((t_edge *)c->in->data[1])->p->a[1]
		- ((t_edge *)c->out->data[0])->p->a[1]) * ratio2;
	o->v12.a[2] = ((t_edge *)c->out->data[0])->p->a[2]
		+ (((t_edge *)c->in->data[1])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]) * ratio2;
	o->v12_uv.n.x = ((t_edge *)c->out->data[0])->uv->n.x
		+ (((t_edge *)c->in->data[1])->uv->n.x
		- ((t_edge *)c->out->data[0])->uv->n.x) * ratio2;
	o->v12_uv.n.y = ((t_edge *)c->out->data[0])->uv->n.y
		+ (((t_edge *)c->in->data[1])->uv->n.y
		- ((t_edge *)c->out->data[0])->uv->n.y) * ratio2;
	o->v_light.a[1] = ((t_edge *)c->out->data[0])->l[0]
		+ (((t_edge *)c->in->data[1])->l[0]
		- ((t_edge *)c->out->data[0])->l[0]) * ratio2;
}

void		clip_1o2i(t_clipper *c, t_vec2d edge[2], t_polygon *p,
	t_polygon *o)
{
	double	ratio;
	double	ratio2;

	ratio = get_intsec_r(((t_edge *)c->out->data[0])->p->c2.vec2d,
		((t_edge *)c->in->data[0])->p->c2.vec2d, edge[0], edge[1]);
	ratio2 = get_intsec_r(((t_edge *)c->out->data[0])->p->c2.vec2d,
		((t_edge *)c->in->data[1])->p->c2.vec2d, edge[0], edge[1]);
	r_clip_1o2i(c, o, ratio);
	r2_clip_1o2i(c, o, ratio2);
	o->tex_id = p->tex_id;
	o->transparency = p->transparency;
	edge_to_polygon(c->in->data[0], o, 2);
	((t_edge *)c->out->data[0])->p->a[0] += (((t_edge *)c->in->data[1])->p->a[0]
		- ((t_edge *)c->out->data[0])->p->a[0]) * ratio2;
	((t_edge *)c->out->data[0])->p->a[1] += (((t_edge *)c->in->data[1])->p->a[1]
		- ((t_edge *)c->out->data[0])->p->a[1]) * ratio2;
	((t_edge *)c->out->data[0])->p->a[2] += (((t_edge *)c->in->data[1])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]) * ratio2;
	((t_edge *)c->out->data[0])->uv->n.x += (((t_edge *)c->in->data[1])->uv->n.x
		- ((t_edge *)c->out->data[0])->uv->n.x) * ratio2;
	((t_edge *)c->out->data[0])->uv->n.y += (((t_edge *)c->in->data[1])->uv->n.y
		- ((t_edge *)c->out->data[0])->uv->n.y) * ratio2;
	((t_edge *)c->out->data[0])->l[0] += (((t_edge *)c->in->data[1])->l[0]
		- ((t_edge *)c->out->data[0])->l[0]) * ratio2;
}
