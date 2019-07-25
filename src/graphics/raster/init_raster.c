/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:52:14 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 00:44:22 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	sort_vertices(t_polygon *p)
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

void	init_raster(t_polygon *p, t_raster *e)
{
	double div[3];

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
	e->transparency = p->transparency;
}
