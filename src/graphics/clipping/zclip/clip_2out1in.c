/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_2out1in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 18:15:34 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 18:22:07 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		clip_2out1in_z(t_clipper *c)
{
	t_edge	*tmp[2];
	double	ratio;

	tmp[0] = c->inside->data[0];
	tmp[1] = c->outside->data[0];
	ratio = tmp[1]->dist / (tmp[0]->p.a[2] - tmp[1]->p.a[2]);
	tmp[1]->p.a[0] += (tmp[0]->p.a[0] - tmp[1]->p.a[0]) * ratio;
	tmp[1]->p.a[1] += (tmp[0]->p.a[1] - tmp[1]->p.a[1]) * ratio;
	tmp[1]->p.a[2] += (tmp[0]->p.a[2] - tmp[1]->p.a[2]) * ratio;
	tmp[1]->uv.a[0] += (tmp[0]->uv.a[0] - tmp[1]->uv.a[0]) * ratio;
	tmp[1]->uv.a[1] += (tmp[0]->uv.a[1] - tmp[1]->uv.a[1]) * ratio;
	tmp[1]->l += (tmp[0]->l - tmp[1]->l) * ratio;
	tmp[1] = c->outside->data[1];
	ratio = tmp[1]->dist / (tmp[0]->p.a[2] - tmp[1]->p.a[2]);
	tmp[1]->p.a[0] += (tmp[0]->p.a[0] - tmp[1]->p.a[0]) * ratio;
	tmp[1]->p.a[1] += (tmp[0]->p.a[1] - tmp[1]->p.a[1]) * ratio;
	tmp[1]->p.a[2] += (tmp[0]->p.a[2] - tmp[1]->p.a[2]) * ratio;
	tmp[1]->uv.a[0] += (tmp[0]->uv.a[0] - tmp[1]->uv.a[0]) * ratio;
	tmp[1]->uv.a[1] += (tmp[0]->uv.a[1] - tmp[1]->uv.a[1]) * ratio;
	tmp[1]->l += (tmp[0]->l - tmp[1]->l) * ratio;
}
