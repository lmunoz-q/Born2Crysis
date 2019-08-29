/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:40:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 19:34:34 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		gthread_raster(t_gthreads *gt, t_gworker *w)
{
	t_raster	r;
	int			i;

	i = -1;
	while (++i < (int)gt->polygon_count)
	{
		if ((int)gt->plist[i].tex_id == -1
				|| (gt->plist[i].transparency && !gt->trans))
			continue ;
		if (gt->plist[i].v01.a[1] > w->end || gt->plist[i].v20.a[1] < w->start)
			continue ;
		init_raster(&gt->plist[i], &r);
		r.h = gt->h;
		r.w = gt->w;
		raster_top(&gt->plist[i], &r, w);
		raster_bot(&gt->plist[i], &r, w);
	}
}

void		rasterize(t_polygon *p, int count, SDL_Surface *surface,
	t_bool trans)
{
	t_gthreads	*gt;
	int			i;

	(void)surface;
	gt = gthread_get(GTHREAD_LAST);
	gt->trans = trans;
	gt->plist = p;
	gt->polygon_count = count;
	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		if (p[i].transparency && !trans)
		{
			transbuff_push(&p[i]);
			continue ;
		}
		sort_vertices(&p[i]);
	}
	gthread_launch(gt);
	gthread_wait(gt);
}
