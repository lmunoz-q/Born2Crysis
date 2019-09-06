/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_substract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:29:17 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:52:45 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4vec4_substract(t_vec4d minuend, t_vec4d subtrahend)
{
	return ((t_vec4d){.n = {
		.x = minuend.n.x - subtrahend.n.x,
		.y = minuend.n.y - subtrahend.n.y,
		.z = minuend.n.z - subtrahend.n.z,
		.w = minuend.n.w - subtrahend.n.w}});
}

t_vec3d	vec3vec3_substract(t_vec3d minuend, t_vec3d subtrahend)
{
	return ((t_vec3d){.n = {
		.x = minuend.n.x - subtrahend.n.x,
		.y = minuend.n.y - subtrahend.n.y,
		.z = minuend.n.z - subtrahend.n.z}});
}

t_vec2d	vec2vec2_substract(t_vec2d minuend, t_vec2d subtrahend)
{
	return ((t_vec2d){.n = {
		.x = minuend.n.x - subtrahend.n.x,
		.y = minuend.n.y - subtrahend.n.y}});
}
