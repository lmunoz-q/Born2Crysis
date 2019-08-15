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

static void		i_clip_1out2in(t_clipper *c, t_polygon *o)
{
	double		ratio;

	ratio = ((t_edge *)c->out->data[0])->dist
		/ (((t_edge *)c->in->data[0])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]);
	o->v01.a[0] = ((t_edge *)c->out->data[0])->p->a[0]
		+ (((t_edge *)c->in->data[0])->p->a[0]
		- ((t_edge *)c->out->data[0])->p->a[0]) * ratio;
	o->v01.a[1] = ((t_edge *)c->out->data[0])->p->a[1]
		+ (((t_edge *)c->in->data[0])->p->a[1]
		- ((t_edge *)c->out->data[0])->p->a[1]) * ratio;
	o->v01.a[2] = ((t_edge *)c->out->data[0])->p->a[2]
		+ (((t_edge *)c->in->data[0])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]) * ratio;
	o->v01_uv.a[0] = ((t_edge *)c->out->data[0])->uv->a[0]
		+ (((t_edge *)c->in->data[0])->uv->a[0]
		- ((t_edge *)c->out->data[0])->uv->a[0]) * ratio;
	o->v01_uv.a[1] = ((t_edge *)c->out->data[0])->uv->a[1]
		+ (((t_edge *)c->in->data[0])->uv->a[1]
		- ((t_edge *)c->out->data[0])->uv->a[1]) * ratio;
	o->v_light.a[0] = ((t_edge *)c->out->data[0])->l[0]
		+ (((t_edge *)c->in->data[0])->l[0]
		- ((t_edge *)c->out->data[0])->l[0]) * ratio;
}

static void		j_clip_1out2in(t_clipper *c, t_polygon *p, t_polygon *o,
	double r2)
{
	o->v12.a[0] = ((t_edge *)c->out->data[0])->p->a[0]
		+ (((t_edge *)c->in->data[1])->p->a[0]
		- ((t_edge *)c->out->data[0])->p->a[0]) * r2;
	o->v12.a[1] = ((t_edge *)c->out->data[0])->p->a[1]
		+ (((t_edge *)c->in->data[1])->p->a[1]
		- ((t_edge *)c->out->data[0])->p->a[1]) * r2;
	o->v12.a[2] = ((t_edge *)c->out->data[0])->p->a[2]
		+ (((t_edge *)c->in->data[1])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]) * r2;
	o->v12_uv.a[0] = ((t_edge *)c->out->data[0])->uv->a[0]
		+ (((t_edge *)c->in->data[1])->uv->a[0]
		- ((t_edge *)c->out->data[0])->uv->a[0]) * r2;
	o->v12_uv.a[1] = ((t_edge *)c->out->data[0])->uv->a[1]
		+ (((t_edge *)c->in->data[1])->uv->a[1]
		- ((t_edge *)c->out->data[0])->uv->a[1]) * r2;
	o->v_light.a[1] = ((t_edge *)c->out->data[0])->l[0]
		+ (((t_edge *)c->in->data[1])->l[0]
		- ((t_edge *)c->out->data[0])->l[0]) * r2;
	o->tex_id = p->tex_id;
	o->transparency = p->transparency;
	edge_to_polygon(c->in->data[0], o, 2);
	((t_edge *)c->out->data[0])->p->a[0] += (((t_edge *)
		c->in->data[1])->p->a[0]
		- ((t_edge *)c->out->data[0])->p->a[0]) * r2;
}

static void		clip_1out2in(t_clipper *c, t_polygon *p, t_polygon *o)
{
	double		r2;

	r2 = ((t_edge *)c->out->data[0])->dist
		/ (((t_edge *)c->in->data[1])->p->a[2]
		- ((t_edge *)c->out->data[0])->p->a[2]);
	i_clip_1out2in(c, o);
	j_clip_1out2in(c, p, o, r2);
	((t_edge *)c->out->data[0])->p->a[1] += (((t_edge *)
		c->in->data[1])->p->a[1]
			- ((t_edge *)c->out->data[0])->p->a[1]) * r2;
	((t_edge *)c->out->data[0])->p->a[2] += (((t_edge *)
		c->in->data[1])->p->a[2]
			- ((t_edge *)c->out->data[0])->p->a[2]) * r2;
	((t_edge *)c->out->data[0])->uv->a[0] += (((t_edge *)
		c->in->data[1])->uv->a[0]
			- ((t_edge *)c->out->data[0])->uv->a[0]) * r2;
	((t_edge *)c->out->data[0])->uv->a[1] += (((t_edge *)
		c->in->data[1])->uv->a[1]
			- ((t_edge *)c->out->data[0])->uv->a[1]) * r2;
	((t_edge *)c->out->data[0])->l[0] += (((t_edge *)
		c->in->data[1])->l[0] - ((t_edge *)c->out->data[0])->l[0]) * r2;
}

int				clip_znear(t_polygon *p, int count)
{
	int			i;
	t_clipper	*c;
	t_edge		e[3];
	int			newcount;

	newcount = count;
	i = -1;
	while (++i < count)
		if (!(p[i].tex_id == -1 || !(c = init_clipper())))
		{
			init_edge(&p[i], e);
			e[0].dist = ZNEAR - e[0].p->a[2];
			e[1].dist = ZNEAR - e[1].p->a[2];
			e[2].dist = ZNEAR - e[2].p->a[2];
			stack_push((e[0].p->a[2] >= ZNEAR) ? c->in : c->out, &e[0]);
			stack_push((e[1].p->a[2] >= ZNEAR) ? c->in : c->out, &e[1]);
			stack_push((e[2].p->a[2] >= ZNEAR) ? c->in : c->out, &e[2]);
			if (c->out->top == 1)
				clip_2out1in_z(c);
			if (c->out->top == 0)
				clip_1out2in(c, &p[i], &p[newcount++]);
			if (c->out->top == 2)
				p[i].tex_id = -1;
		}
	return (newcount);
}
