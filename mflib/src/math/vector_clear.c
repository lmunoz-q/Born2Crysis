/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 23:33:00 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:52:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

void		vec4_clear(t_vec4d *vec)
{
	vec->n.x = 0;
	vec->n.y = 0;
	vec->n.z = 0;
	vec->n.w = 0;
}

void		vec3_clear(t_vec3d *vec)
{
	vec->n.x = 0;
	vec->n.y = 0;
	vec->n.z = 0;
}

void		vec2_clear(t_vec2d *vec)
{
	vec->n.x = 0;
	vec->n.y = 0;
}
