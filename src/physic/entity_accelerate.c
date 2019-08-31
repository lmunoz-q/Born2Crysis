/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_accelerate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 16:10:19 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 16:10:20 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>
#include <world.h>

t_vec3d	entity_accelerate(t_entity e, t_vec3d a)
{
	t_vec3d	t;

	t = vec3vec3_add(e.velocity, a);
	if (vec3_dot(t, t) <= e.sector->physics.speed_limit * e.sector->physics.speed_limit)
		return (t);
	return (e.velocity);
}
