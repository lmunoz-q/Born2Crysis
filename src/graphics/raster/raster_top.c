/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_top.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:50:47 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 17:50:48 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	i_raster_top(t_polygon *p, t_raster *e, int i)
{
	e->start = p->v01.a[0] + ((double)i - p->v01.a[1]) * e->x_s;
	e->end = p->v01.a[0] + ((double)i - p->v01.a[1]) * e->x_s2;
	e->zstart = p->v01.a[2] + ((double)i - p->v01.a[1]) * e->z_s;
	e->zend = p->v01.a[2] + ((double)i - p->v01.a[1]) * e->z_s2;
	e->ustart = ((p->v01_uv.a[0] + ((double)i - p->v01.a[1]) * e->u_s))
		* e->tex->size.n.x;
	e->uend = ((p->v01_uv.a[0] + ((double)i - p->v01.a[1]) * e->u_s2))
		* e->tex->size.n.x;
	e->vstart = ((p->v01_uv.a[1] + ((double)i - p->v01.a[1]) * e->v_s))
		* e->tex->size.n.y;
	e->vend = ((p->v01_uv.a[1] + ((double)i - p->v01.a[1]) * e->v_s2))
		* e->tex->size.n.y;
	e->lstart = (p->v_light.a[0] + ((double)i - p->v01.a[1]) * e->l_s) * A;
	e->lend = (p->v_light.a[0] + ((double)i - p->v01.a[1]) * e->l_s2) * A;
}

void		raster_top(t_polygon *p, t_raster *e, t_gworker *w)
{
	int			i;
	int			ps;

	e->tex = get_texture_from_id(p->tex_id);
	ps = w->start;
	if (ps != 0)
		ps--;
	i = (p->v01.a[1] >= w->start) ? p->v01.a[1] : ps;
	while (++i < p->v12.a[1] && i >= 0 && i < e->h && i < w->end)
	{
		i_raster_top(p, e, i);
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
