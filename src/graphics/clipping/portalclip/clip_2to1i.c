/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_2to1i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 20:01:15 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/15 20:01:27 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		clip_2o1i(t_stack *out, t_stack *in, t_vec2d edge[2])
{
	double r;

	r = get_intsec_r(((t_edge *)out->data[0])->p->c2.vec2d,
		((t_edge *)in->data[0])->p->c2.vec2d, edge[0], edge[1]);
	((t_edge *)out->data[0])->p->a[0] += (((t_edge *)in->data[0])->p->a[0]
		- ((t_edge *)out->data[0])->p->a[0]) * r;
	((t_edge *)out->data[0])->p->a[1] += (((t_edge *)in->data[0])->p->a[1]
		- ((t_edge *)out->data[0])->p->a[1]) * r;
	((t_edge *)out->data[0])->p->a[2] += (((t_edge *)in->data[0])->p->a[2]
		- ((t_edge *)out->data[0])->p->a[2]) * r;
	((t_edge *)out->data[0])->uv->n.x += (((t_edge *)in->data[0])->uv->n.x
		- ((t_edge *)out->data[0])->uv->n.x) * r;
	((t_edge *)out->data[0])->uv->n.y += (((t_edge *)in->data[0])->uv->n.y
		- ((t_edge *)out->data[0])->uv->n.y) * r;
	((t_edge *)out->data[0])->l[0] += (((t_edge *)in->data[0])->l[0]
		- ((t_edge *)out->data[0])->l[0]) * r;
	r = get_intsec_r(((t_edge *)out->data[1])->p->c2.vec2d,
		((t_edge *)in->data[0])->p->c2.vec2d, edge[0], edge[1]);
	((t_edge *)out->data[1])->p->a[0] += (((t_edge *)in->data[0])->p->a[0]
		- ((t_edge *)out->data[1])->p->a[0]) * r;
	((t_edge *)out->data[1])->p->a[1] += (((t_edge *)in->data[0])->p->a[1]
		- ((t_edge *)out->data[1])->p->a[1]) * r;
	((t_edge *)out->data[1])->p->a[2] += (((t_edge *)in->data[0])->p->a[2]
		- ((t_edge *)out->data[1])->p->a[2]) * r;
	((t_edge *)out->data[1])->uv->n.x += (((t_edge *)in->data[0])->uv->n.x
		- ((t_edge *)out->data[1])->uv->n.x) * r;
	((t_edge *)out->data[1])->uv->n.y += (((t_edge *)in->data[0])->uv->n.y
		- ((t_edge *)out->data[1])->uv->n.y) * r;
	((t_edge *)out->data[1])->l[0] += (((t_edge *)in->data[0])->l[0]
		- ((t_edge *)out->data[1])->l[0]) * r;
}
