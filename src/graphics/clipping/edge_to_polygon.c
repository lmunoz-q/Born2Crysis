/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge_to_polygon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 10:56:02 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/12 10:56:15 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	edge_to_polygon(t_edge *e, t_polygon *p, int i)
{
	p->v_light.a[i] = e->l;
	if (i == 0)
	{
		p->v01 = e->p;
		p->v01_uv.a[0] = e->uv.a[0];
		p->v01_uv.a[1] = e->uv.a[1];
	}
	if (i == 1)
	{
		p->v12 = e->p;
		p->v12_uv.a[0] = e->uv.a[0];
		p->v12_uv.a[1] = e->uv.a[1];
	}
	if (i == 2)
	{
		p->v20 = e->p;
		p->v20_uv.a[0] = e->uv.a[0];
		p->v20_uv.a[1] = e->uv.a[1];
	}
}
