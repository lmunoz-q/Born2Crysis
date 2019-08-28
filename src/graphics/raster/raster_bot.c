/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_bot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:50:37 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 17:50:39 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	iraster_bot(t_polygon *p, t_raster *e, int i)
{
	e->start = p->v12.a[0] + ((double)i - p->v12.a[1]) * e->x_s3;
	e->end = p->v01.a[0] + ((double)i - p->v01.a[1]) * e->x_s2;
	e->zstart = p->v12.a[2] + ((double)i - p->v12.a[1]) * e->z_s3;
	e->zend = p->v01.a[2] + ((double)i - p->v01.a[1]) * e->z_s2;
	e->ustart = (p->v12_uv.a[0] + ((double)i
		- p->v12.a[1]) * e->u_s3) * e->tex->size.n.x;
	e->uend = (p->v01_uv.a[0] + ((double)i
		- p->v01.a[1]) * e->u_s2) * e->tex->size.n.x;
	e->vstart = (p->v12_uv.a[1] + ((double)i
		- p->v12.a[1]) * e->v_s3) * e->tex->size.n.y;
	e->vend = (p->v01_uv.a[1] + ((double)i
		- p->v01.a[1]) * e->v_s2) * e->tex->size.n.y;
	e->lstart = (p->v_light.a[1] + ((double)i - p->v12.a[1]) * e->l_s3) * A;
	e->lend = (p->v_light.a[0] + ((double)i - p->v01.a[1]) * e->l_s2) * A;
}

void		raster_bot(t_polygon *p, t_raster *e, t_gworker *w)
{
	int			i;
	int			ps;

	ps = w->start;
	if (ps != 0)
		ps--;
	i = (p->v12.a[1] >= w->start) ? p->v12.a[1] : ps;
	while (++i < p->v20.a[1] && i >= 0 && i < e->h && i < w->end)
	{
		iraster_bot(p, e, i);
		if (e->start > e->end)
		{
			mf_swap_int(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
		raster_line(e, &w->zbuff[e->w * (i - w->start)],
			&w->pixels[e->w * (i - w->start)], p->transparency);
	}
}
