/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 13:40:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/09 17:53:57 by mfischer         ###   ########.fr       */
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

static void	init_raster(t_polygon *p, t_raster *e)
{
	double div[3];

	sort_vertices(p);
	div[0] = fabs(p->v12[1] - p->v01[1]);
	div[1] = fabs(p->v20[1] - p->v01[1]);
	div[2] = fabs(p->v20[1] - p->v12[1]);
	e->x_s = (div[0]) ? (p->v12[0] - p->v01[0]) / div[0] : 0.0;
	e->x_s2 = (div[1]) ? (p->v20[0] - p->v01[0]) / div[1] : 0.0;
	e->x_s3 = (div[2]) ? (p->v20[0] - p->v12[0]) / div[2] : 0.0;
	e->z_s = (div[0]) ? (p->v12[2] - p->v01[2]) / div[0] : 0.0;
	e->z_s2 = (div[1]) ? (p->v20[2] - p->v01[2]) / div[1] : 0.0;
	e->z_s3 = (div[2]) ? (p->v20[2] - p->v12[2]) / div[2] : 0.0;
	e->u_s = (div[0]) ? (p->v12_uv[0] - p->v01_uv[0]) / div[0] : 0.0;
	e->u_s2 = (div[1]) ? (p->v20_uv[0] - p->v01_uv[0]) / div[1] : 0.0;
	e->u_s3 = (div[2]) ? (p->v20_uv[0] - p->v12_uv[0]) / div[2] : 0.0;
	e->v_s = (div[0]) ? (p->v12_uv[1] - p->v01_uv[1]) / div[0] : 0.0;
	e->v_s2 = (div[1]) ? (p->v20_uv[1] - p->v01_uv[1]) / div[1] : 0.0;
	e->v_s3 = (div[2]) ? (p->v20_uv[1] - p->v12_uv[1]) / div[2] : 0.0;
	e->l_s = (div[0]) ? (p->v_light[1] - p->v_light[0]) / div[0] : 0.0;
	e->l_s2 = (div[1]) ? (p->v_light[2] - p->v_light[0]) / div[1] : 0.0;
	e->l_s3 = (div[2]) ? (p->v_light[2] - p->v_light[1]) / div[2] : 0.0;
}

static void	raster_line(t_raster *e, int i, SDL_Surface *m, SDL_Surface *tex)
{
	double	steps[4];
	int		tmp[3];

	steps[0] = (e->zend - e->zstart) / (e->end - e->start);
	steps[1] = (e->uend - e->ustart) / (e->end - e->start);
	steps[2] = (e->vend - e->vstart) / (e->end - e->start);
	steps[3] = (e->lend - e->lstart) / (e->end - e->start);
	tmp[0] = i * m->w;
	while (e->start < e->end)
	{
		tmp[1] = tmp[0] + e->start;
		if (win->zbuffer[tmp[1]] > e->zstart)
		{
			win->zbuffer[tmp[1]] = e->zstart;
			tmp[2] = (tex->h - (int)(e->vstart / e->zstart * tex->h))
					* tex->w + (e->ustart / e->zstart * tex->w);
			((unsigned int*)m->pixels)[tmp[1]] = ((unsigned int*)tex)[tmp[2]];
		}
		e->zstart += steps[0];
		e->ustart += steps[1];
		e->vstart += steps[2];
		e->lstart += steps[3];
		e->start++;
	}
}

void		rasterize(t_polygon *p, int count, SDL_Surface *surface)
{
	t_raster e;
	int i;

	i = -1;
	while (++i < count)
	{
		if (p[i].tex_id == -1)
			continue ;
		init_raster(p, &e);
	}
}