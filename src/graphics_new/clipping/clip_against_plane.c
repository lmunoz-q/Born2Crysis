/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_against_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 14:04:22 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/07 15:52:13 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int			classify_points(t_polygon *p, double plane_p[3], double plane_n[3])
{

	t_edge		edges[3];

	init_edge(p, edges);
	edges[0].dist = dist_pointplane(plane_n, plane_p, edges[0].p);
	edges[0].dist = dist_pointplane(plane_n, plane_p, edges[0].p);
	edges[0].dist = dist_pointplane(plane_n, plane_p, edges[0].p);
}

int			clip_against_plane(t_polygon *p, int count, double plane_p[3],
														double plane_n[3])
{
	int			i;
	int			newcount;
	t_clipper	*clip;
	
	newcount = count;
	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		if (!(clip = init_clipper()))
			return (newcount);
		newcount = classify_points(&p[i], plane_p, plane_n);
		
	}
	return (newcount);
}