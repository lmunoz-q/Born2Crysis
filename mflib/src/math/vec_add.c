/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:28:53 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 16:40:24 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d			vec4vec4_add(t_vec4d addend, t_vec4d augend)
{
	return ((t_vec4d){.n = {.x = addend.n.x + augend.n.x,
							.y = addend.n.y + augend.n.y,
							.z = addend.n.z + augend.n.z,
							.w = addend.n.w + augend.n.w}});
}

t_vec3d			vec3vec3_add(t_vec3d addend, t_vec3d augend)
{
	return ((t_vec3d){.n = {.x = addend.n.x + augend.n.x,
		.y = addend.n.y + augend.n.y,
		.z = addend.n.z + augend.n.z}});
}

t_vec2d			vec2vec2_add(t_vec2d addend, t_vec2d augend)
{
	return ((t_vec2d){.n = {.x = addend.n.x + augend.n.x,
		.y = addend.n.y + augend.n.y}});
}
