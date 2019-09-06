/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 13:41:00 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:52:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

double	vec4_dot(t_vec4d vec1, t_vec4d vec2)
{
	return (vec1.n.x * vec2.n.x
		+ vec1.n.y * vec2.n.y
		+ vec1.n.z * vec2.n.z
		+ vec1.n.w * vec2.n.w);
}

double	vec3_dot(t_vec3d vec1, t_vec3d vec2)
{
	return (vec1.n.x * vec2.n.x
			+ vec1.n.y * vec2.n.y
			+ vec1.n.z * vec2.n.z);
}

double	vec2_dot(t_vec2d vec1, t_vec2d vec2)
{
	return (vec1.n.x * vec2.n.x
			+ vec1.n.y * vec2.n.y);
}
