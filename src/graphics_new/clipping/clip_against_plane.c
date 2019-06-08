/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_against_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:04:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/08 23:02:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	classify_points(t_polygon *p, double plane_p[3], double plane_n[3], t_clipper *c)
{

	t_edge		edges[3];

	init_edge(p, edges);
	edges[0].dist = dist_pointplane(plane_n, plane_p, edges[0].p);
	edges[1].dist = dist_pointplane(plane_n, plane_p, edges[1].p);
	edges[2].dist = dist_pointplane(plane_n, plane_p, edges[2].p);
	stack_push((edges[0].dist >= 0) ? c->inside : c->outside, &edges[0]);
	stack_push((edges[1].dist >= 0) ? c->inside : c->outside, &edges[1]);
	stack_push((edges[2].dist >= 0) ? c->inside : c->outside, &edges[2]);
}

int			clip_against_plane(t_polygon *p, int count, double plane_p[3],
														double plane_n[3])
{
	int			i;
	t_clipper	*clip;
	
	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		if (!(clip = init_clipper()))
			return (count);
		classify_points(&p[i], plane_p, plane_n, clip);
		if (clip->outside->top == 1)
			clip_2out1in(clip);
		if (clip->outside->top == 0)
			clip_1out2in(clip, p, count, &p[count++]);
		if (clip->outside->top == -1)
			p[i].tex_id = -1;
	}
	return (count);
}