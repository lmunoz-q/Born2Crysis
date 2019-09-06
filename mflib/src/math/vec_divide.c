/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_divide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:23:29 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/17 16:27:40 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4vec4_divide(t_vec4d dividend, t_vec4d divisor)
{
	return ((t_vec4d){.a = {
		dividend.n.x / divisor.n.x,
		dividend.n.y / divisor.n.y,
		dividend.n.z / divisor.n.z,
		dividend.n.w / divisor.n.w}});
}

t_vec3d	vec3vec3_divide(t_vec3d dividend, t_vec3d divisor)
{
	return ((t_vec3d){.a = {
		dividend.n.x / divisor.n.x,
		dividend.n.y / divisor.n.y,
		dividend.n.z / divisor.n.z}});
}

t_vec2d	vec2vec2_divide(t_vec2d dividend, t_vec2d divisor)
{
	return ((t_vec2d){.a = {
		dividend.n.x / divisor.n.x,
		dividend.n.y / divisor.n.y}});
}
