/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_alpha_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:18:03 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 17:18:04 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

static void	i_draw_alpha_line(t_raster *e, t_vec4d steps)
{
	e->zstart += steps.a[0];
	e->ustart += steps.a[1];
	e->vstart += steps.a[2];
	e->lstart += steps.a[3];
}

void		draw_alpha_line(t_raster *e, double *zbuff, Uint32 *p,
	t_vec4d steps)
{
	double			a1;
	double			a;
	Uint32			c1;
	Uint32			c2;

	(void)steps;
	a1 = (float)e->transparency / 255.0;
	a = (1.0 - a1);
	while (e->start < e->end)
	{
		if (e->start >= 0 && e->start < e->w && zbuff[e->start] > e->zstart)
		{
			c1 = texture_get_pixel(((e->vstart / e->zstart)),
				(e->ustart / e->zstart), e->tex);
			c2 = p[e->start];
			p[e->start] = (((Uint32)(((float)(c1 & R) * a1) + ((float)(c2 & R)
				* a)) & R) + ((Uint32)(((float)(c1 & G) * a1) + ((float)(c2 & G)
					* a)) & G) + ((Uint32)(((float)(c1 & B) * a1) + ((float)
						(c2 & B) * a)) & B) + (((c2 & A) | ((unsigned int)
							((e->lstart / e->zstart) * ((double)((unsigned int)
							a1 & A))))) & A));
		}
		i_draw_alpha_line(e, steps);
		e->start++;
	}
}
