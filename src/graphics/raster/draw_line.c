/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:09:04 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/09/01 15:25:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	draw_line(t_raster *e, double *zbuff, Uint32 *p, t_vec4d steps)
{
	while (e->start < e->end)
	{
		if (e->start >= 0 && e->start < e->w && zbuff[e->start] > e->zstart)
		{
			zbuff[e->start] = e->zstart;
			p[e->start] = (texture_get_pixel(((e->vstart / e->zstart)),
				(e->ustart / e->zstart), e->tex) & (0x00FFFFFF))
				| (((unsigned int)(e->lstart / e->zstart) & 0xFF000000));
		}
		e->zstart += steps.a[0];
		e->ustart += steps.a[1];
		e->vstart += steps.a[2];
		e->lstart += steps.a[3];
		e->start++;
	}
}
