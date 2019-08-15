/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_insec_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:54:51 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/15 19:55:01 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double		get_intsec_r(t_vec2d a1, t_vec2d a2, t_vec2d b1, t_vec2d b2)
{
	t_vec2d	p;

	p = line_intsect_2d(a1, a2, b1, b2);
	return (vec2_magnitude(vec2vec2_substract(p, a1))
		/ vec2_magnitude(vec2vec2_substract(a2, a1)));
}
