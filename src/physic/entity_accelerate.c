/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_accelerate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/00/00 00:00:00 by hmartzol          #+#    #+#             */
/*   Updated: 2000/00/00 00:00:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <physic.h>
#include <world.h>

t_vec3d	entity_accelerate(t_eidos_frame e, t_vec3d a)
{
	t_vec3d	t;

	if (e.sector == NULL)
		return ((t_vec3d){{0, 0, 0}});
	t = vec3vec3_add(e.velocity, a);
	if (vec3_dot(t, t) <= e.sector->physics.speed_limit
			* e.sector->physics.speed_limit)
		return (t);
	return (e.velocity);
}
