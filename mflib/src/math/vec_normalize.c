/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_normalize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:51:18 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/09 16:36:49 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4_normalize(t_vec4d vector)
{
	return (vec4scalar_divide(vector, vec4_magnitude(vector)));
}

t_vec3d	vec3_normalize(t_vec3d vector)
{
	return (vec3scalar_divide(vector, vec3_magnitude(vector)));
}

t_vec2d	vec2_normalize(t_vec2d vector)
{
	return (vec2scalar_divide(vector, vec2_magnitude(vector)));
}
