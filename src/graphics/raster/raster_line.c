/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 18:04:28 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/28 18:04:30 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	raster_line(t_raster *e, double *zbuff, Uint32 *p, int transparency)
{
	t_vec4d	steps;
	double	tmp2;

	tmp2 = 1.0 / (e->end - e->start);
	steps.a[0] = (e->zend - e->zstart) * tmp2;
	steps.a[1] = (e->uend - e->ustart) * tmp2;
	steps.a[2] = (e->vend - e->vstart) * tmp2;
	steps.a[3] = (e->lend - e->lstart) * tmp2;
	if (transparency)
		draw_alpha_line(e, zbuff, p, steps);
	else
		draw_line(e, zbuff, p, steps);
}
