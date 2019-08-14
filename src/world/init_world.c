/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:47:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/20 19:01:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool			init_world(t_world *world)
{
	t_polygon	*buff;

	if (!(buff = load_buffer(world)))
		return (FALSE);
	set_polygon_buffer(buff);
	init_portals(world);
	set_world(world);
	return (TRUE);
}
