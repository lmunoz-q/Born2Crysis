/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_2o1i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 12:06:49 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/08 12:59:06 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		clip_2out1in(t_clipper *c)
{
	double ratio;
	t_edge	*tmp[2];

	tmp[0] = c->outside->data[0];
	tmp[1] = c->inside->data[0];
	ratio = calc_ratio_3d(c->outside->data[0], c->inside->data[0]);
	tmp[0]->p[0] += (tmp[1]->p[0] - tmp[0]->p[0]) * ratio;
	tmp[0]->p[1] += (tmp[1]->p[1] - tmp[0]->p[1]) * ratio;
	tmp[0]->p[2] += (tmp[1]->p[2] - tmp[0]->p[2]) * ratio;
	tmp[0]->uv[0] += (tmp[1]->uv[0] - tmp[0]->uv[0]) * ratio;
	tmp[0]->uv[1] += (tmp[1]->uv[1] - tmp[0]->uv[1]) * ratio;
	*tmp[0]->l += (*tmp[1]->l - *tmp[0]->l) * ratio;
	tmp[0] = c->outside->data[1];
	ratio = calc_ratio_3d(c->outside->data[1], c->inside->data[0]);
	tmp[0]->p[0] += (tmp[1]->p[0] - tmp[0]->p[0]) * ratio;
	tmp[0]->p[1] += (tmp[1]->p[1] - tmp[0]->p[1]) * ratio;
	tmp[0]->p[2] += (tmp[1]->p[2] - tmp[0]->p[2]) * ratio;
	tmp[0]->uv[0] += (tmp[1]->uv[0] - tmp[0]->uv[0]) * ratio;
	tmp[0]->uv[1] += (tmp[1]->uv[1] - tmp[0]->uv[1]) * ratio;
	*tmp[0]->l += (*tmp[1]->l - *tmp[0]->l) * ratio;
}