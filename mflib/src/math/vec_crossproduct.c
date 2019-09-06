/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_crossproduct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 18:21:54 by mfischer          #+#    #+#             */
/*   Updated: 2019/04/13 14:52:19 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec4d	vec4vec4_crossproduct(t_vec4d v1, t_vec4d v2)
{
	return ((t_vec4d){.a = {
		(v1.a[1] * v2.a[2]) - (v1.a[2] * v2.a[1]),
		(v1.a[2] * v2.a[0]) - (v1.a[0] * v2.a[2]),
		(v1.a[0] * v2.a[1]) - (v1.a[1] * v2.a[0]), 0.0}});
}

t_vec3d	vec3vec3_crossproduct(t_vec3d v1, t_vec3d v2)
{
	return ((t_vec3d){.a = {
		(v1.a[1] * v2.a[2]) - (v1.a[2] * v2.a[1]),
		(v1.a[2] * v2.a[0]) - (v1.a[0] * v2.a[2]),
		(v1.a[0] * v2.a[1]) - (v1.a[1] * v2.a[0])}});
}
