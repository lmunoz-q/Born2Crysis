/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:40:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 12:52:47 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void draw_line(t_raster *e, double *zbuff, Uint32 *p, double steps[4])
{
	while (e->start < e->end)
	{
		if (e->start >= 0 && e->start < e->w && zbuff[e->start] > e->zstart)
		{
			zbuff[e->start] = e->zstart;
			p[e->start] = (texture_get_pixel(
			((e->vstart / e->zstart)), (e->ustart / e->zstart), e->tex)
			&(0x00FFFFFF)) | ((unsigned int)(e->lstart) & 0xFF000000);
		}
		e->zstart += steps[0];
		e->ustart += steps[1];
		e->vstart += steps[2];
		e->lstart += steps[3];
		e->start++;
	}
}

static void draw_alpha_line(t_raster *e, double *zbuff, Uint32 *p, double steps[4])
{
	float			a1;
	float			a;
	Uint32			c1;
	Uint32			c2;

	a1 = (float)e->transparency / 255.0;
	a = (1.0 - a1);
	while (e->start < e->end)
	{
		if (e->start >= 0 && e->start < e->w && zbuff[e->start] > e->zstart)
		{
			c1 = texture_get_pixel(((e->vstart / e->zstart)), (e->ustart / e->zstart), e->tex);
			c2 = p[e->start];
			p[e->start] = (((Uint32)(((float)(c1 & 0x00ff0000) * a1) + ((float)(c2 & 0x00ff0000) * a)) & 0x00ff0000)
			+				((Uint32)(((float)(c1 & 0x0000ff00) * a1) + ((float)(c2 & 0x0000ff00) * a)) & 0x0000ff00)
			+				((Uint32)(((float)(c1 & 0x000000ff) * a1) + ((float)(c2 & 0x000000ff) * a)) & 0x000000ff)
			+ (((c2 & 0xff000000) | ((unsigned int)(e->lstart * (double)a))) & 0xFF000000));
		}
		e->zstart += steps[0];
		e->ustart += steps[1];
		e->vstart += steps[2];
		e->lstart += steps[3];
		e->start++;
	}
}

static void	raster_line(t_raster *e, double	*zbuff, Uint32	*p, int transparency)
{
	double	steps[4];
	double 	tmp2;
	
	tmp2 = 1.0 / (e->end - e->start);
	steps[0] = (e->zend - e->zstart) * tmp2;
	steps[1] = (e->uend - e->ustart) * tmp2;
	steps[2] = (e->vend - e->vstart) * tmp2;
	steps[3] = (e->lend - e->lstart) * tmp2;
	if (transparency)
		draw_alpha_line(e, zbuff, p, steps);
	else
		draw_line(e, zbuff, p, steps);
}

void	raster_top(t_polygon *p, t_raster *e, t_gworker *w)
{
	int			i;
	int			ps;

	e->tex = get_texture_from_id(p->tex_id);
	ps = w->start;
	if (ps != 0)
		ps--;
	i = (p->v01[1] >= w->start) ? p->v01[1] : ps;
	while (++i < p->v12[1] && i >= 0 && i < e->h && i < w->end)
	{
		e->start = p->v01[0] + ((double)i - p->v01[1]) * e->x_s;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->x_s2;
		e->zstart = p->v01[2] + ((double)i - p->v01[1]) * e->z_s;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->z_s2;
		e->ustart = ((p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s)) * e->tex->size.x;
		e->uend = ((p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s2)) * e->tex->size.x;
		e->vstart = ((p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s)) * e->tex->size.y;
		e->vend = ((p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s2)) * e->tex->size.y;
		e->lstart = (p->v_light[0] + ((double)i - p->v01[1]) * e->l_s) * 0xff000000;
		e->lend = (p->v_light[0] + ((double)i - p->v01[1]) * e->l_s2) * 0xff000000;
		if (e->start > e->end)
		{
			mf_swap_int(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
		raster_line(e, &w->zbuff[e->w * (i - w->start)], &w->pixels[e->w * (i - w->start)], p->transparency);
	}
}

void	raster_bot(t_polygon *p, t_raster *e, t_gworker *w)
{
	int			i;
	int			ps;

	ps = w->start;
	if (ps != 0)
		ps--;
	i = (p->v12[1] >= w->start) ? p->v12[1] : ps;
	while (++i < p->v20[1] && i >= 0 && i < e->h && i < w->end)
	{
		e->start = p->v12[0] + ((double)i - p->v12[1]) * e->x_s3;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->x_s2;
		e->zstart = p->v12[2] + ((double)i - p->v12[1]) * e->z_s3;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->z_s2;
		e->ustart = (p->v12_uv[0] + ((double)i - p->v12[1]) * e->u_s3) * e->tex->size.x;
		e->uend = (p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s2) * e->tex->size.x;
		e->vstart = (p->v12_uv[1] + ((double)i - p->v12[1]) * e->v_s3) * e->tex->size.y;
		e->vend = (p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s2) * e->tex->size.y;
		e->lstart = (p->v_light[1] + ((double)i - p->v12[1]) * e->l_s3) * 0xff000000;
		e->lend = (p->v_light[0] + ((double)i - p->v01[1]) * e->l_s2) * 0xff000000;
		if (e->start > e->end)
		{
			mf_swap_int(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
		raster_line(e, &w->zbuff[e->w * (i - w->start)], &w->pixels[e->w * (i - w->start)], p->transparency);
	}
}

void		gthread_raster(t_gthreads *gt, t_gworker *w)
{
	t_raster	r;
	int 		i;

	i = -1;
	while (++i < gt->polygon_count)
	{
		if (gt->plist[i].tex_id == -1 || (gt->plist[i].transparency && !gt->trans))
			continue ;
		if (gt->plist[i].v01[1] > w->end || gt->plist[i].v20[1] < w->start)
			continue ;
		init_raster(&gt->plist[i], &r);
		r.h = gt->h;
		r.w = gt->w;
		raster_top(&gt->plist[i], &r, w);
		raster_bot(&gt->plist[i], &r, w);
	}
}

void		rasterize(t_polygon *p, int count, SDL_Surface *surface, t_bool trans)
{
	t_gthreads	*gt;
	int i;

	(void)surface;
	gt = gthread_get();
	gt->trans = trans;
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
