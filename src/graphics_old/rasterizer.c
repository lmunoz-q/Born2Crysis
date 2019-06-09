/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 20:04:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 19:29:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		first_triangle(t_polygon *p, t_raster *e, t_libui_window *win)
{
	int		i;
	int		tmp;
	int		tmp2;
	int		tmp3;
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
		tmp3 = i * win->surface->w;
		while (e->start < e->end)
		{
			tmp = tmp3 + e->start;
			if (win->zbuffer[tmp] > e->zstart)
			{
				win->zbuffer[tmp] = e->zstart;
				tmp2 = (p->texture->h - (int)(e->vstart / e->zstart * p->texture->h)) * p->texture->w + (e->ustart / e->zstart * p->texture->w);
				((unsigned int*)surf)[tmp] = ((unsigned int*)tex)[tmp2];
			}
			e->lstart += e->lstep;
			e->zstart += e->zstep;
			e->ustart += e->ustep;
			e->vstart += e->vstep;
			e->start++;
		}
	}
}

void		second_triangle(t_polygon *p, t_raster *e, t_libui_window *win)
{
	int		i;
	int		tmp;
	int		tmp2;
	int		tmp3;
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
		tmp3 = i * win->surface->w;
		while (e->start < e->end)
		{
			tmp = tmp3 + e->start;
			if (win->zbuffer[tmp] > e->zstart)
			{
				win->zbuffer[tmp] = e->zstart;
				tmp2 = (p->texture->h - (int)(e->vstart / e->zstart * p->texture->h)) * p->texture->w + (e->ustart / e->zstart * p->texture->w);
				((unsigned int*)surf)[tmp] = ((unsigned int*)tex)[tmp2];
			}
			e->lstart += e->lstep;
			e->zstart += e->zstep;
			e->ustart += e->ustep;
			e->vstart += e->vstep;
			e->start++;
		}
	}
}

void		rasterizer(t_polygonlist *l, t_libui_window *win)
{
	t_raster		edge;
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
