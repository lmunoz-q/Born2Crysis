/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_magnitude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 17:38:55 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:52:30 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

double	vec4_magnitude(t_vec4d vector)
{
	return (sqrt((vector.n.x * vector.n.x) + (vector.n.y * vector.n.y)
			+ (vector.n.z * vector.n.z) + (vector.n.w * vector.n.w)));
}

double	vec3_magnitude(t_vec3d vector)
{
	return (sqrt((vector.n.x * vector.n.x) + (vector.n.y * vector.n.y)
			+ (vector.n.z * vector.n.z)));
}

double	vec2_magnitude(t_vec2d vector)
{
	return (sqrt((vector.n.x * vector.n.x) + (vector.n.y * vector.n.y)));
}
