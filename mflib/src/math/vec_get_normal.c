/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 21:52:27 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/30 22:07:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

t_vec3d	vec3p_get_normal(t_vec3d p1, t_vec3d p2, t_vec3d p3)
{
	return (vec3_normalize(vec3vec3_crossproduct(vec3vec3_substract(p2, p1),
		vec3vec3_substract(p3, p1))));
}
