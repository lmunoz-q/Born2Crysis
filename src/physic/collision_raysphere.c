/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_raysphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 19:40:29 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/23 21:02:23 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physic.h"

t_bool	collision_raysphere(t_vec3d ray_a, t_vec3d ray_p, t_vec3d sphere,
	double radius)
{
	double res;

	res = vec3vec3_angle(ray_a, vec3vec3_substract(sphere, ray_p));
	res = tan(res) * vec3vec3_dist(sphere, ray_p);
	printf("%f\n", res);
	if (res > radius)
		return (FALSE);
	return (TRUE);
}
