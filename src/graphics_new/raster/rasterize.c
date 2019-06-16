/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:40:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/14 13:47:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	raster_line(t_inner_raster *e, int i, SDL_Surface *m, t_vec2i tex)
{
	double	steps[4];
	int		tmp;
	double	*zbuff;

	zbuff = get_zbuff();
	steps[0] = (e->zend - e->zstart) / (e->end - e->start);
	steps[1] = (e->uend - e->ustart) / (e->end - e->start);
	steps[2] = (e->vend - e->vstart) / (e->end - e->start);
	steps[3] = (e->lend - e->lstart) / (e->end - e->start);
	while (e->start < e->end)
	{
		tmp = i * m->w + e->start;
		if (zbuff[tmp] > e->zstart)
		{
			zbuff[tmp] = e->zstart;
			((uint32_t *)m->pixels)[tmp] = texture_get_pixel(tex.y - (int)
			(e->vstart / e->zstart * tex.y), e->ustart / e->zstart * tex.x); 
		}
		e->zstart += steps[0];
		e->ustart += steps[1];
		e->vstart += steps[2];
		e->lstart += steps[3];
		e->start++;
	}
}

void		raster_line_top(void *param, t_stat_param sparam)
{
	t_inner_raster	ir;
	t_thread_raster	*r;

	r = param;
	ir.start = r->p->v01[0] + (sparam.d - r->p->v01[1]) * r->ras->x_s;
	ir.end = r->p->v01[0] + (sparam.d - r->p->v01[1]) * r->ras->x_s2;
	ir.zstart = r->p->v01[2] + (sparam.d - r->p->v01[1]) * r->ras->z_s;
	ir.zend = r->p->v01[2] + (sparam.d - r->p->v01[1]) * r->ras->z_s2;
	ir.ustart = r->p->v01_uv[0] + (sparam.d - r->p->v01[1]) * r->ras->u_s;
	ir.uend = r->p->v01_uv[0] + (sparam.d - r->p->v01[1]) * r->ras->u_s2;
	ir.vstart = r->p->v01_uv[1] + (sparam.d - r->p->v01[1]) * r->ras->v_s;
	ir.vend = r->p->v01_uv[1] + (sparam.d - r->p->v01[1]) * r->ras->v_s2;
	ir.lstart = r->p->v_light[0] + (sparam.d - r->p->v01[1]) * r->ras->l_s;
	ir.lend = r->p->v_light[0] + (sparam.d - r->p->v01[1]) * r->ras->l_s2;
	if (ir.start > ir.end)
	{
		mf_swap_doubles(&ir.start, &ir.end, 1);
		mf_swap_doubles(&ir.zstart, &ir.zend, 1);
		mf_swap_doubles(&ir.ustart, &ir.uend, 1);
		mf_swap_doubles(&ir.vstart, &ir.vend, 1);
		mf_swap_doubles(&ir.lstart, &ir.lend, 1);
	}
	raster_line(&ir, sparam.d, r->surface, r->tex);
}

static void	raster_top(t_polygon *p, t_raster *e, SDL_Surface *surface, t_vec2i tex)
{
	int					i;
	t_thread_pool		*pool;
	t_thread_raster		param;
	t_thread_pool_work	work;

	pool = get_thread_pool();
	param.p = p;
	param.ras = e;
	param.surface = surface;
	param.tex = tex;
	work.f = raster_line_top;
	work.param = &param;
	i = p->v01[1];
	while (++i < p->v12[1])
	{
		work.s_param.d = i;
		thread_pool_push_work(pool, work);
	}
	//thread_pool_wait(pool);
}

void		raster_line_bot(void *param, t_stat_param sparam)
{
	t_inner_raster	ir;
	t_thread_raster	*r;

	r = param;
	ir.start = r->p->v12[0] + (sparam.d - r->p->v12[1]) * r->ras->x_s3;
	ir.end = r->p->v01[0] + (sparam.d - r->p->v01[1]) * r->ras->x_s2;
	ir.zstart = r->p->v12[2] + (sparam.d - r->p->v12[1]) * r->ras->z_s3;
	ir.zend = r->p->v01[2] + (sparam.d - r->p->v01[1]) * r->ras->z_s2;
	ir.ustart = r->p->v12_uv[0] + (sparam.d - r->p->v12[1]) * r->ras->u_s3;
	ir.uend = r->p->v01_uv[0] + (sparam.d - r->p->v01[1]) * r->ras->u_s2;
	ir.vstart = r->p->v12_uv[1] + (sparam.d - r->p->v12[1]) * r->ras->v_s3;
	ir.vend = r->p->v01_uv[1] + (sparam.d - r->p->v01[1]) * r->ras->v_s2;
	ir.lstart = r->p->v_light[1] + (sparam.d - r->p->v12[1]) * r->ras->l_s3;
	ir.lend = r->p->v_light[0] + (sparam.d - r->p->v01[1]) * r->ras->l_s2;
	if (ir.start > ir.end)
	{
		mf_swap_doubles(&ir.start, &ir.end, 1);
		mf_swap_doubles(&ir.zstart, &ir.zend, 1);
		mf_swap_doubles(&ir.ustart, &ir.uend, 1);
		mf_swap_doubles(&ir.vstart, &ir.vend, 1);
		mf_swap_doubles(&ir.lstart, &ir.lend, 1);
	}
	raster_line(&ir, sparam.d, r->surface, r->tex);
}

static void	raster_bot(t_polygon *p, t_raster *e, SDL_Surface *surface, t_vec2i tex)
{
	int					i;
	t_thread_pool		*pool;
	t_thread_raster		param;
	t_thread_pool_work	work;

	pool = get_thread_pool();
	param.p = p;
	param.ras = e;
	param.surface = surface;
	param.tex = tex;
	work.f = raster_line_top;
	work.param = &param;
	i = p->v12[1];
	while (++i < p->v20[1])
	{
		work.s_param.d = i;
		thread_pool_push_work(pool, work);
	}
	//thread_pool_wait(pool);
}

void		rasterize(t_polygon *p, int count, SDL_Surface *surface)
{
	t_raster	e;
	t_texture tex;
	int i;

	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		load_texture(p[i].tex_id);
		tex = get_current_texture();
		init_raster(&p[i], &e);
		raster_top(&p[i], &e, surface, tex->size);
		raster_bot(&p[i], &e, surface, tex->size);
	}
}
