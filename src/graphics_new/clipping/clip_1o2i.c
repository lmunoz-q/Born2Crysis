/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_1o2i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:55:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 00:46:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void		gen_new_polygon(t_edge *e[3], t_polygon *p, double ratios[2])
{
	p->v01[0] = e[0]->p[0] + ((e[1]->p[0] - e[0]->p[0]) * ratios[0]);
	p->v01[1] = e[0]->p[1] + ((e[1]->p[1] - e[0]->p[1]) * ratios[0]);
	p->v01[2] = e[0]->p[2] + ((e[1]->p[2] - e[0]->p[2]) * ratios[0]);
	p->v01_uv[0] = e[0]->uv[0] + ((e[1]->uv[0] - e[0]->uv[0]) * ratios[0]);
	p->v01_uv[1] = e[0]->uv[1] + ((e[1]->uv[1] - e[0]->uv[1]) * ratios[0]);
	p->v_light[0] = *e[0]->l + ((*e[1]->l - *e[0]->l) * ratios[0]);
	p->v12[0] = e[0]->p[0] + ((e[2]->p[0] - e[0]->p[0]) * ratios[1]);
	p->v12[1] = e[0]->p[1] + ((e[2]->p[1] - e[0]->p[1]) * ratios[1]);
	p->v12[2] = e[0]->p[2] + ((e[2]->p[2] - e[0]->p[2]) * ratios[1]);
	p->v12_uv[0] = e[0]->uv[0] + ((e[2]->uv[0] - e[0]->uv[0]) * ratios[1]);
	p->v12_uv[1] = e[0]->uv[1] + ((e[2]->uv[1] - e[0]->uv[1]) * ratios[1]);
	p->v_light[1] = *e[0]->l + ((*e[2]->l - *e[0]->l) * ratios[1]);
	vec4_copy(p->v20, e[1]->p);
	vec4_copy(p->v20_uv, e[1]->uv);
	p->v_light[2] = *e[1]->l;
}

static void		update_edge(t_edge *e[3], double ratio)
{
	e[0]->p[0] += (e[1]->p[0] - e[0]->p[0]) * ratio;
	e[0]->p[1] += (e[1]->p[1] - e[0]->p[1]) * ratio;
	e[0]->p[2] += (e[1]->p[2] - e[0]->p[2]) * ratio;
	e[0]->uv[0] += (e[1]->uv[0] - e[0]->uv[0]) * ratio;
	e[0]->uv[0] += (e[1]->uv[0] - e[0]->uv[0]) * ratio;
	*e[0]->l += (*e[1]->l - *e[0]->l) * ratio;
}

void			clip_1out2in(t_clipper *c, t_polygon *p, int count, t_polygon *o)
{
	double	ratios[2];
	t_edge	*edge[3];

	edge[0] = c->outside->data[0];
	edge[1] = c->inside->data[0];
	edge[2] = c->inside->data[1];
	ratios[0] = calc_ratio_3d(c->outside->data[0], c->inside->data[0]);
	ratios[1] = calc_ratio_3d(c->outside->data[0], c->inside->data[1]);
	vec3_copy(p[count].normal, o->normal);
	p[count].tex_id = o->tex_id;
	gen_new_polygon(edge, &p[count], ratios);
	update_edge(edge, ratios[0]);
}