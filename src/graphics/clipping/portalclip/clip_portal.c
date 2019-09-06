/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_portal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:41:28 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 21:05:13 by mfischer         ###   ########.fr       */
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

Uint32			clip_polygon(t_polygon *p, Uint32 count, t_vec2d e[2])
{
	t_edge		point[3];
	Uint32		newcount;
	t_clipper	*c;
	int32_t		i;

	newcount = count;
	i = -1;
	while (++i < (int32_t)count)
		if (!(p[i].tex_id == -1 || !(c = init_clipper())))
		{
			init_edge(&p[i], point);
			stack_push((is_right(e[0], e[1],
				p[i].v01.c2.vec2d) ? c->in : c->out), &point[0]);
			stack_push((is_right(e[0], e[1],
				p[i].v12.c2.vec2d) ? c->in : c->out), &point[1]);
			stack_push((is_right(e[0], e[1],
				p[i].v20.c2.vec2d) ? c->in : c->out), &point[2]);
			if (c->out->top == 2)
				p[i].tex_id = (Uint32)-1;
			if (c->out->top == 1)
				clip_2o1i(c->out, c->in, e);
			if (c->out->top == 0)
				clip_1o2i(c, e, &p[i], &p[newcount++]);
		}
	return (newcount);
}

Uint32			portal_clip(t_polygon *p, Uint32 count, int width, int height)
{
	count = clip_polygon(p, count,
		(t_vec2d[2]){{.a = {0, height + 1}}, {.a = {0, 0}}});
	count = clip_polygon(p, count,
		(t_vec2d[2]){{.a = {0, 0}}, {.a = {width + 1, 0}}});
	count = clip_polygon(p, count,
		(t_vec2d[2]){{.a = {width + 1, 0}}, {.a = {width + 1, height + 1}}});
	count = clip_polygon(p, count,
		(t_vec2d[2]){{.a = {width + 1, height + 1}}, {.a = {0, height + 1}}});
	return (count);
}
