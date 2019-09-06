/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_multiply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:23:29 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 16:27:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4vec4_multiply(t_vec4d vec1, t_vec4d vec2)
{
	return ((t_vec4d){.a = {
		vec1.n.x * vec2.n.x,
		vec1.n.y * vec2.n.y,
		vec1.n.z * vec2.n.z,
		vec1.n.w * vec2.n.w}});
}

t_vec3d	vec3vec3_multiply(t_vec3d vec1, t_vec3d vec2)
{
	return ((t_vec3d){.a = {
		vec1.n.x * vec2.n.x,
		vec1.n.y * vec2.n.y,
		vec1.n.z * vec2.n.z}});
}

t_vec2d	vec2vec2_multiply(t_vec2d vec1, t_vec2d vec2)
{
	return ((t_vec2d){.a = {
		vec1.n.x * vec2.n.x,
		vec1.n.y * vec2.n.y}});
}
