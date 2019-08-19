/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:47:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 12:39:41 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool		init_world(t_world *world)
{
	if (!load_buffer(world))
		return (FALSE);
	init_portals(world);
	set_world(world);
	return (TRUE);
}
