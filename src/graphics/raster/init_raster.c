/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raster.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:52:14 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 21:13:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	sort_vertices(t_polygon *p)
{
	if (p->v12.a[1] < p->v01.a[1])
	{
		mf_swap_doubles(p->v12.a, p->v01.a, 3);
		mf_swap_doubles(p->v12_uv.a, p->v01_uv.a, 2);
		mf_swap_doubles(&p->v_light.a[1], &p->v_light.a[0], 1);
	}
	if (p->v20.a[1] < p->v01.a[1])
	{
		mf_swap_doubles(p->v20.a, p->v01.a, 3);
		mf_swap_doubles(p->v20_uv.a, p->v01_uv.a, 2);
		mf_swap_doubles(&p->v_light.a[2], &p->v_light.a[0], 1);
	}
	if (p->v20.a[1] < p->v12.a[1])
	{
		mf_swap_doubles(p->v20.a, p->v12.a, 3);
		mf_swap_doubles(p->v20_uv.a, p->v12_uv.a, 2);
		mf_swap_doubles(&p->v_light.a[2], &p->v_light.a[1], 1);
	}
}

void	init_raster(t_polygon *p, t_raster *e)
{
	double div[3];

	div[0] = fabs(p->v12.a[1] - p->v01.a[1]);
	div[1] = fabs(p->v20.a[1] - p->v01.a[1]);
	div[2] = fabs(p->v20.a[1] - p->v12.a[1]);
	e->x_s = (div[0]) ? (p->v12.a[0] - p->v01.a[0]) / div[0] : 0.0;
	e->x_s2 = (div[1]) ? (p->v20.a[0] - p->v01.a[0]) / div[1] : 0.0;
	e->x_s3 = (div[2]) ? (p->v20.a[0] - p->v12.a[0]) / div[2] : 0.0;
	e->z_s = (div[0]) ? (p->v12.a[2] - p->v01.a[2]) / div[0] : 0.0;
	e->z_s2 = (div[1]) ? (p->v20.a[2] - p->v01.a[2]) / div[1] : 0.0;
	e->z_s3 = (div[2]) ? (p->v20.a[2] - p->v12.a[2]) / div[2] : 0.0;
	e->u_s = (div[0]) ? (p->v12_uv.a[0] - p->v01_uv.a[0]) / div[0] : 0.0;
	e->u_s2 = (div[1]) ? (p->v20_uv.a[0] - p->v01_uv.a[0]) / div[1] : 0.0;
	e->u_s3 = (div[2]) ? (p->v20_uv.a[0] - p->v12_uv.a[0]) / div[2] : 0.0;
	e->v_s = (div[0]) ? (p->v12_uv.a[1] - p->v01_uv.a[1]) / div[0] : 0.0;
	e->v_s2 = (div[1]) ? (p->v20_uv.a[1] - p->v01_uv.a[1]) / div[1] : 0.0;
	e->v_s3 = (div[2]) ? (p->v20_uv.a[1] - p->v12_uv.a[1]) / div[2] : 0.0;
	e->l_s = (div[0]) ? (p->v_light.a[1] - p->v_light.a[0]) / div[0] : 0.0;
	e->l_s2 = (div[1]) ? (p->v_light.a[2] - p->v_light.a[0]) / div[1] : 0.0;
	e->l_s3 = (div[2]) ? (p->v_light.a[2] - p->v_light.a[1]) / div[2] : 0.0;
	e->transparency = p->transparency;
}
