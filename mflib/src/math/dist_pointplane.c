/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_pointplane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:39:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 16:34:36 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mfmath.h"

double		dist_pointplane(t_vec3d plane_n, t_vec3d plane_p, t_vec3d point)
{
	return (vec3_dot(vec3vec3_substract(point, plane_p), plane_n));
}
