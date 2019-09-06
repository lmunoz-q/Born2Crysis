/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecscalar_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:06:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/30 18:07:58 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4scalar_add(t_vec4d vec, double scalar)
{
	vec.n.x += scalar;
	vec.n.y += scalar;
	vec.n.z += scalar;
	vec.n.w += scalar;
	return (vec);
}

t_vec3d	vec3scalar_add(t_vec3d vec, double scalar)
{
	vec.n.x += scalar;
	vec.n.y += scalar;
	vec.n.z += scalar;
	return (vec);
}

t_vec2d	vec2scalar_add(t_vec2d vec, double scalar)
{
	vec.n.x += scalar;
	vec.n.y += scalar;
	return (vec);
}
