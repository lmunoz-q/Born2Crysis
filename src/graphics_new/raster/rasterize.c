/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:40:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 19:52:37 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	raster_line(t_raster *e, int i, SDL_Surface *m, SDL_Surface *tex)
{
	double	steps[4];
	int		tmp[2];
	double	*zbuff;

	zbuff = get_zbuff();
	steps[0] = (e->zend - e->zstart) / (e->end - e->start);
	steps[1] = (e->uend - e->ustart) / (e->end - e->start);
	steps[2] = (e->vend - e->vstart) / (e->end - e->start);
	steps[3] = (e->lend - e->lstart) / (e->end - e->start);
	tmp[0] = i * m->w;
	while (e->start < e->end)
	{
		tmp[1] = tmp[0] + e->start;
		if (zbuff[tmp[1]] > e->zstart)
		{
			zbuff[tmp[1]] = e->zstart;
			((unsigned int*)m->pixels)[tmp[1]] = ((unsigned int*)tex)[
			(int)((tex->h - (int)(e->vstart / e->zstart * tex->h))
				* tex->w + (e->ustart / e->zstart * tex->w))];
		}
		e->zstart += steps[0];
		e->ustart += steps[1];
		e->vstart += steps[2];
		e->lstart += steps[3];
		e->start++;
	}
}

static void	raster_top(t_polygon *p, t_raster *e, SDL_Surface *surface, SDL_Surface *tex)
{
	int			i;

	i = p->v01[1];
	while (++i < p->v12[1])
	{
		e->start = p->v01[0] + ((double)i - p->v01[1]) * e->x_s;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->x_s2;
		e->zstart = p->v01[2] + ((double)i - p->v01[1]) * e->z_s;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->z_s2;
		e->ustart = p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s;
		e->uend = p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s2;
		e->vstart = p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s;
		e->vend = p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s2;
		e->lstart = p->v_light[0] + ((double)i - p->v01[1]) * e->l_s;
		e->lend = p->v_light[0] + ((double)i - p->v01[1]) * e->l_s2;
		if (e->start > e->end)
		{
			mf_swap_doubles(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
		raster_line(e, i, surface, tex);
	}
}

static void	raster_bot(t_polygon *p, t_raster *e, SDL_Surface *surface, SDL_Surface *tex)
{
	int i;

	i = p->v12[1];
	while (++i < p->v20[1])
	{
		e->start = p->v12[0] + ((double)i - p->v12[1]) * e->x_s3;
		e->end = p->v01[0] + ((double)i - p->v01[1]) * e->x_s2;
		e->zstart = p->v12[2] + ((double)i - p->v12[1]) * e->z_s3;
		e->zend = p->v01[2] + ((double)i - p->v01[1]) * e->z_s2;
		e->ustart = p->v12_uv[0] + ((double)i - p->v12[1]) * e->u_s3;
		e->uend = p->v01_uv[0] + ((double)i - p->v01[1]) * e->u_s2;
		e->vstart = p->v12_uv[1] + ((double)i - p->v12[1]) * e->v_s3;
		e->vend = p->v01_uv[1] + ((double)i - p->v01[1]) * e->v_s2;
		e->lstart = p->v_light[1] + ((double)i - p->v12[1]) * e->l_s3;
		e->lend = p->v_light[0] + ((double)i - p->v01[1]) * e->l_s2;
		if (e->start > e->end)
		{
			mf_swap_doubles(&e->start, &e->end, 1);
			mf_swap_doubles(&e->zstart, &e->zend, 1);
			mf_swap_doubles(&e->ustart, &e->uend, 1);
			mf_swap_doubles(&e->vstart, &e->vend, 1);
			mf_swap_doubles(&e->lstart, &e->lend, 1);
		}
	}
}

void		rasterize(t_polygon *p, int count, SDL_Surface *surface)
{
	t_raster	e;
	SDL_Surface	*tex;
	int i;

	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		//GET TEXTURE
		init_raster(p, &e);
		raster_top(&p[i], &e, surface, tex);
		raster_bot(&p[i], &e, surface, tex);
	}
}