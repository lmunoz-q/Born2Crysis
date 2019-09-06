/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecscalar_multiply.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:45:06 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:52:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4scalar_multiply(t_vec4d vec, double scalar)
{
	vec.n.x *= scalar;
	vec.n.y *= scalar;
	vec.n.z *= scalar;
	vec.n.w *= scalar;
	return (vec);
}

t_vec3d	vec3scalar_multiply(t_vec3d vec, double scalar)
{
	vec.n.x *= scalar;
	vec.n.y *= scalar;
	vec.n.z *= scalar;
	return (vec);
}

t_vec2d	vec2scalar_multiply(t_vec2d vec, double scalar)
{
	vec.n.x *= scalar;
	vec.n.y *= scalar;
	return (vec);
}
