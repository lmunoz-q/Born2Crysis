/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:26:41 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 19:33:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

double	vec4vec4_angle(t_vec4d v1, t_vec4d v2)
{
	return (acos((vec4_dot(v1, v2)) / (vec4_magnitude(v1)
	* vec4_magnitude(v2))));
}

double	vec3vec3_angle(t_vec3d v1, t_vec3d v2)
{
	return (acos((vec3_dot(v1, v2)) / (vec3_magnitude(v1)
	* vec3_magnitude(v2))));
}

double	vec2vec2_angle(t_vec2d v1, t_vec2d v2)
{
	return (acos((vec2_dot(v1, v2)) / (vec2_magnitude(v1)
	* vec2_magnitude(v2))));
}
