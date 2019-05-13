/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 20:04:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 16:09:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static inline void	sort_vertices(t_polygon *p)
{
	if (p->v12[1] < p->v01[1])
	{
        mf_swap_doubles(p->v12, p->v01, 3);
		mf_swap_doubles(p->v12_uv, p->v01_uv, 2);
		mf_swap_doubles(&p->v_light[1], &p->v_light[0], 1);
	}
    if (p->v20[1] < p->v01[1])
	{
        mf_swap_doubles(p->v20, p->v01, 3);
		mf_swap_doubles(p->v20_uv, p->v01_uv, 2);
		mf_swap_doubles(&p->v_light[2], &p->v_light[0], 1);
	}
    if (p->v20[1] < p->v12[1])
	{
        mf_swap_doubles(p->v20, p->v12, 3);
		mf_swap_doubles(p->v20_uv, p->v12_uv, 2);
		mf_swap_doubles(&p->v_light[2], &p->v_light[1], 1);
	}
}

static void	init_raster(t_polygon *p, t_edge *e)
{
	sort_vertices(p);
	e->dx = p->v12[0] - p->v01[0];
	e->dy = p->v12[1] - p->v01[1];
	e->dz = p->v12[2] - p->v01[2];
	e->du = p->v12_uv[0] - p->v01_uv[0];
	e->dv = p->v12_uv[1] - p->v01_uv[1];
	e->dl = p->v_light[1] - p->v_light[0];
	e->dx2 = p->v20[0] - p->v01[0];
	e->dy2 = p->v20[1] - p->v01[1];
	e->dz2 = p->v20[2] - p->v01[2];
	e->du2 = p->v20_uv[0] - p->v01_uv[0];
	e->dv2 = p->v20_uv[1] - p->v01_uv[1];
	e->dl2 = p->v_light[2] - p->v_light[0];
	e->dx3 = p->v20[0] - p->v12[0];
	e->dy3 = p->v20[1] - p->v12[1];
	e->dz3 = p->v20[2] - p->v12[2];
	e->du3 = p->v20_uv[0] - p->v12_uv[0];
	e->dv3 = p->v20_uv[1] - p->v12_uv[1];
	e->dl3 = p->v_light[2] - p->v_light[1];
	e->dx_step = (e->dy) ? e->dx / fabs(e->dy) : 0.0;
	e->dx_step2 = (e->dy2) ? e->dx2 / fabs(e->dy2) : 0.0;
	e->dx_step3 = (e->dy3) ? e->dx3 / fabs(e->dy3) : 0.0;
	e->dz_step = (e->dy) ? e->dz / fabs(e->dy) : 0.0;
	e->dz_step2 = (e->dy2) ? e->dz2 / fabs(e->dy2) : 0.0;
	e->dz_step3 = (e->dy3) ? e->dz3 / fabs(e->dy3) : 0.0;
	e->du_step = (e->dy) ? e->du / fabs(e->dy) : 0.0;
	e->du_step2 = (e->dy2) ? e->du2 / fabs(e->dy2) : 0.0;
	e->du_step3 = (e->dy3) ? e->du3 / fabs(e->dy3) : 0.0;
	e->dv_step = (e->dy) ? e->dv / fabs(e->dy) : 0.0;
	e->dv_step2 = (e->dy2) ? e->dv2 / fabs(e->dy2) : 0.0;
	e->dv_step3 = (e->dy3) ? e->dv3 / fabs(e->dy3) : 0.0;
	e->dl_step = (e->dy) ? e->dl / fabs(e->dy) : 0.0;
	e->dl_step2 = (e->dy2) ? e->dl2 / fabs(e->dy2) : 0.0;
	e->dl_step3 = (e->dy3) ? e->dl3 / fabs(e->dy3) : 0.0;
}

void		first_triangle(t_polygon *p, t_edge *e, t_libui_window *win)
{
	int		i;
	int		tmp;
	void	*tex;
	void	*surf;

	tex = p->texture->pixels;
	(void)tex;
	surf = win->surface->pixels;
	i = p->v01[1];
	while (++i < p->v12[1])
	{
		e->start = p->v01[0] + ((double)i - p->v01[1]) * e->dx_step;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->dx_step2;
		e->zstart = p->v01[2] + ((double)i - p->v01[1]) * e->dz_step;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->dz_step2;
		e->ustart = p->v01_uv[0] + ((double)i - p->v01[1]) * e->du_step;
		e->uend = p->v01_uv[0] + ((double)i - p->v01[1]) * e->du_step2;
		e->vstart = p->v01_uv[1] + ((double)i - p->v01[1]) * e->dv_step;
		e->vend = p->v01_uv[1] + ((double)i - p->v01[1]) * e->dv_step2;
		e->lstart = p->v_light[0] + ((double)i - p->v01[1]) * e->dl_step;
		e->lend = p->v_light[0] + ((double)i - p->v01[1]) * e->dl_step2;
		if (e->start > e->end)
		{
			mf_swap_doubles(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
		e->zstep = (e->zend - e->zstart) / (e->end - e->start);
		e->ustep = (e->uend - e->ustart) / (e->end - e->start);
		e->vstep = (e->vend - e->vstart) / (e->end - e->start);
		e->lstep = (e->lend - e->lstart) / (e->end - e->start);
		while (e->start < e->end)
		{
			tmp = i * win->surface->w + e->start;
			if (e->start >= 0 && e->end < win->surface->w && i >= 0
				&& i < win->surface->h && win->zbuffer[tmp] > e->zstart)
			{
				win->zbuffer[tmp] = e->zstart;
				((unsigned int*)surf)[tmp] = ((unsigned int*)tex)[(int)((int)(e->vstart * 64.0) * 64 + (e->ustart * 64.0))];
			}
			e->lstart += e->lstep;
			e->zstart += e->zstep;
			e->ustart += e->ustep;
			e->vstart += e->vstep;
			e->start++;
		}
	}
}

void		second_triangle(t_polygon *p, t_edge *e, t_libui_window *win)
{
	int		i;
	int		tmp;
	void	*tex;
	void	*surf;

	tex = p->texture->pixels;
	surf = win->surface->pixels;
	i = p->v12[1];
	while (++i < p->v20[1])
	{
		e->start = p->v12[0] + ((double)i - p->v12[1]) * e->dx_step3;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->dx_step2;
		e->zstart = p->v12[2] + ((double)i - p->v12[1]) * e->dz_step3;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->dz_step2;
		e->ustart = p->v12_uv[0] + ((double)i - p->v12[1]) * e->du_step3;
		e->uend = p->v01_uv[0] + ((double)i - p->v01[1]) * e->du_step2;
		e->vstart = p->v12_uv[1] + ((double)i - p->v12[1]) * e->dv_step3;
		e->vend = p->v01_uv[1] + ((double)i - p->v01[1]) * e->dv_step2;
		e->lstart = p->v_light[1] + ((double)i - p->v12[1]) * e->dl_step3;
		e->lend = p->v_light[0] + ((double)i - p->v01[1]) * e->dl_step2;
		if (e->start > e->end)
		{
			mf_swap_doubles(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
		e->zstep = (e->zend - e->zstart) / (e->end - e->start);
		e->lstep = (e->lend - e->lstart) / (e->end - e->start);
		e->ustep = (e->uend - e->ustart) / (e->end - e->start);
		e->vstep = (e->vend - e->vstart) / (e->end - e->start);
		while (e->start < e->end)
		{
			tmp = i * win->surface->w + e->start;
			if (e->start >= 0 && e->end < win->surface->w && i >= 0
				&& i < win->surface->h && win->zbuffer[tmp] > e->zstart)
			{
				win->zbuffer[tmp] = e->zstart;
				(void)tex;
				((unsigned int*)surf)[tmp] = ((unsigned int*)tex)[(int)((int)(e->vstart * 64.0) * 64 + (e->ustart * 64.0))];
			}
			e->lstart += e->lstep;
			e->zstart += e->zstep;
			e->ustart += e->ustep;
			e->vstart += e->vstep;
			e->start++;
		}
	}
}

void		rasterize(t_polygonlist *l, t_libui_window *win)
{
	t_edge		edge;
	t_polygon	*p;
	t_node		*head;

	head = l->list;
	while (head)
	{
		p = head->data;
		if (!p->active || !p->texture)
		{
			head = head->next;
			continue ;
		}
		init_raster(p, &edge);
		first_triangle(p, &edge, win);
		second_triangle(p, &edge, win);
		head = head->next;
	}
}
