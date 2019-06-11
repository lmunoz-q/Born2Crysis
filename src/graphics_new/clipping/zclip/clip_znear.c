/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_znear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:01:12 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 19:23:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	classify_points(t_edge *edges, t_clipper *c)
{
	edges[0].dist = ZNEAR - edges[0].p[2];
	edges[1].dist = ZNEAR - edges[1].p[2];
	edges[2].dist = ZNEAR - edges[2].p[2];
	stack_push((edges[0].p[2] >= ZNEAR) ? c->inside : c->outside, &edges[0]);
	stack_push((edges[1].p[2] >= ZNEAR) ? c->inside : c->outside, &edges[1]);
	stack_push((edges[2].p[2] >= ZNEAR) ? c->inside : c->outside, &edges[2]);
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
		//if (clip->outside->top == 1)
			//clip_2out1in_z(clip);
		//if (clip->outside->top == 0)
		//	p[i].tex_id = -1;
		//	clip_1out2in(clip, &p[i], &p[newcount++]);
		if (clip->inside->top != 2)
			p[i].tex_id = -1;
	}
	return (newcount);
}
