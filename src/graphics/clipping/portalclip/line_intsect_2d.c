/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_intsect_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:38:32 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/15 19:38:40 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_vec2d	line_intsect_2d(t_vec2d a1, t_vec2d a2, t_vec2d b1, t_vec2d b2)
{
	t_vec3d	p[2];
	t_vec2d	res;
	double	delta;

	p[0].n.y = a2.a[1] - a1.a[1];
	p[0].n.x = a1.a[0] - a2.a[0];
	p[0].n.z = p[0].n.y * a1.a[0] + p[0].n.x * a1.a[1];
	p[1].n.y = b2.a[1] - b1.a[1];
	p[1].n.x = b1.a[0] - b2.a[0];
	p[1].n.z = p[1].n.y * b1.a[0] + p[1].n.x * b1.a[1];
	delta = p[0].n.y * p[1].n.x - p[1].n.y * p[0].n.x;
	res.n.x = ((p[1].n.x * p[0].n.z) - (p[0].n.x * p[1].n.z)) / delta;
	res.n.y = ((p[0].n.y * p[1].n.z) - (p[1].n.y * p[0].n.z)) / delta;
	return (res);
}
