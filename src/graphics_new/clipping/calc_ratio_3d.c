/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ratio_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:33:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 12:16:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"


double		calc_ratio_3d(t_edge *e1, t_edge *e2)
{
	double div;

	div = (e2->p[0] - e1->p[0]) * (e2->p[0] - e1->p[0]);
	div += (e2->p[1] - e1->p[1]) * (e2->p[1] - e1->p[1]);
	div += (e2->p[2] - e1->p[2]) * (e2->p[2] - e1->p[2]);
	printf("div: %f   dist: %f   ratio: %f\n", div, e1->dist, (e1->dist * e1->dist) / div);
	return ((e1->dist * e1->dist) / div);
}