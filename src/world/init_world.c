/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:47:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 20:39:09 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

t_bool			init_world(t_world *world)
{
	/*if (!load_buffer(world))
		return (FALSE);*/
	init_portals(world);
	return (TRUE);
}
