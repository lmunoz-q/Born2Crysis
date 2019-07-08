/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:40:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/09 01:02:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void draw_line(t_raster *e, double *zbuff, Uint32 *p, double steps[4])
{
	t_texture texture;

	texture = get_current_texture();
	while (e->start < e->end)
	{
		if (zbuff[e->start] > e->zstart)
		{
			zbuff[e->start] = e->zstart;
			p[e->start] = (texture_get_pixel(
			((e->vstart / e->zstart)), (e->ustart / e->zstart), texture)
			&(0x00FFFFFF)) | ((unsigned int)(e->lstart) & 0xFF000000);
		}
		
		e->zstart += steps[0];
		e->ustart += steps[1];
		e->vstart += steps[2];
		e->lstart += steps[3];
		e->start++;
	}
}

static void	raster_line(t_raster *e, int i, SDL_Surface *m)
{
	double	steps[4];
	double 	tmp2;
	double	*zbuff;
	Uint32	*p;

	zbuff = get_zbuff();
	tmp2 = 1.0 / (e->end - e->start);
	steps[0] = (e->zend - e->zstart) * tmp2;
	steps[1] = (e->uend - e->ustart) * tmp2;
	steps[2] = (e->vend - e->vstart) * tmp2;
	steps[3] = (e->lend - e->lstart) * tmp2;
	zbuff = &zbuff[(int)(i * m->w)];
	p = &((Uint32 *)m->pixels)[(int)(i * m->w)];
	draw_line(e, zbuff, p, steps);
}

static void	raster_top(t_polygon *p, t_raster *e, SDL_Surface *surface, t_vec2i tex)
{
	int			i;

	i = p->v01[1];
	while (++i < p->v12[1])
	{
		e->start = p->v01[0] + ((double)i - p->v01[1]) * e->x_s;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->x_s2;
		e->zstart = p->v01[2] + ((double)i - p->v01[1]) * e->z_s;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->z_s2;
		e->ustart = ((p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s)) * tex.x;
		e->uend = ((p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s2)) * tex.x;
		e->vstart = ((p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s)) * tex.y;
		e->vend = ((p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s2)) * tex.y;
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
		raster_line(e, i, surface);
	}
}

static void	raster_bot(t_polygon *p, t_raster *e, SDL_Surface *surface, t_vec2i tex)
{
	int i;

	i = p->v12[1];
	while (++i < p->v20[1])
	{
		e->start = p->v12[0] + ((double)i - p->v12[1]) * e->x_s3;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->x_s2;
		e->zstart = p->v12[2] + ((double)i - p->v12[1]) * e->z_s3;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->z_s2;
		e->ustart = (p->v12_uv[0] + ((double)i - p->v12[1]) * e->u_s3) * tex.x;
		e->uend = (p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s2) * tex.x;
		e->vstart = (p->v12_uv[1] + ((double)i - p->v12[1]) * e->v_s3) * tex.y;
		e->vend = (p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s2) * tex.y;
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
		raster_line(e, i, surface);
	}
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
