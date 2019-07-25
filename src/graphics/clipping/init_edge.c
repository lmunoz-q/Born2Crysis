/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 23:44:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/07 15:03:48 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		init_edge(t_polygon	*p, t_edge edge[3])
{
	edge[0].p = p->v01;
	edge[0].uv = p->v01_uv;
	edge[0].l = p->v_light.a[0];
	edge[1].p = p->v12;
	edge[1].uv = p->v12_uv;
	edge[1].l = p->v_light.a[1];
	edge[2].p = p->v20;
	edge[2].uv = p->v20_uv;
	edge[2].l = p->v_light.a[2];
}
