/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:46:09 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:53:03 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

void		vec4_init(t_vec4d *vec)
{
	vec->n.x = 0;
	vec->n.y = 0;
	vec->n.z = 0;
	vec->n.w = 1;
}

void		vec3_init(t_vec3d *vec)
{
	vec->n.x = 0;
	vec->n.y = 0;
	vec->n.z = 1;
}

void		vec2_init(t_vec2d *vec)
{
	vec->n.x = 0;
	vec->n.y = 0;
}
