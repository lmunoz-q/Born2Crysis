/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kf_walk_forward.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:34:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/18 00:18:10 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_funcs.h"

void	kf_walk_forward(void *param)
{
	t_e		*e;
	double	vec[3];
	double	vec2[3];

	e = param;
	vec3_copy(vec, e->camera.pos);
	vec3scalar_multiply(e->input_map.mouse.front, 0.2, vec2);
	vec3vec3_substract(vec, vec2, e->camera.pos);
}
