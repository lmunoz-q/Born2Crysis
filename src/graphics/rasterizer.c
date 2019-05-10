/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 20:04:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/10 14:38:35 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static inline void	sort_vertices(t_polygon *p)
{
	if (p->v12[1] < p->v01[1])
	{
        mf_swap_doubles(p->v12, p->v01, 3);
		mf_swap_doubles(p->v12_uw, p->v01_uw, 2);
		mf_swap_doubles(&p->v_light[1], &p->v_light[0], 1);
	}
    if (p->v20[1] < p->v01[1])
	{
        mf_swap_doubles(p->v20, p->v01, 3);
		mf_swap_doubles(p->v20_uw, p->v01_uw, 2);
		mf_swap_doubles(&p->v_light[2], &p->v_light[0], 1);
	}
    if (p->v20[1] < p->v12[1])
	{
        mf_swap_doubles(p->v20, p->v12, 3);
		mf_swap_doubles(p->v20_uw, p->v12_uw, 2);
		mf_swap_doubles(&p->v_light[2], &p->v_light[1], 1);
	}
}

static void	init_raster(t_polygon *p, t_edge *e)
{
	sort_vertices(p);
	e->dx = p->v12[0] - p->v01[0];
	e->dy = p->v12[1] - p->v01[1];
	e->dz = p->v12[2] - p->v01[2];
	e->du = p->v12_uw[0] - p->v01_uw[0];
	e->dw = p->v12_uw[1] - p->v01_uw[1];
	e->dl = p->v_light[1] - p->v_light[0];
	e->dx2 = p->v20[0] - p->v01[0];
	e->dy2 = p->v20[1] - p->v01[1];
	e->dz2 = p->v20[2] - p->v01[2];
	e->du2 = p->v20_uw[0] - p->v01_uw[0];
	e->dw2 = p->v20_uw[1] - p->v01_uw[1];
	e->dl2 = p->v_light[2] - p->v_light[0];
	e->dx_step = (e->dy) ? e->dx / fabs(e->dy) : 0.0;
	e->dx_step2 = (e->dy2) ? e->dx2 / fabs(e->dy2) : 0.0;
	e->dz_step = (e->dy) ? e->dz / fabs(e->dy) : 0.0;
	e->dz_step2 = (e->dy2) ? e->dz2 / fabs(e->dy2) : 0.0;
	e->du_step = (e->dw) ? e->du / fabs(e->dw) : 0.0;
	e->du_step2 = (e->dw2) ? e->du2 / fabs(e->dw2) : 0.0;
	e->dl_step = (e->dy) ? e->dl / fabs(e->dy) : 0.0;
	e->dl_step2 = (e->dy2) ? e->dl2 / fabs(e->dy2) : 0.0;
}

void		first_triangle(t_polygon *p, t_edge *e)
{
	int i;

	i = -1;
	while (e->dy && ++i < p->v12[1])
	{
		
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
		head = head->next;
	}
}
