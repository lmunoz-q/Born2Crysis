/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:47:05 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/04 23:09:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "world.h"

void		init_indexes(t_world *world)
{
	int i;
	int j;

	i = -1;
	while (++i < world->sectornum)
	{
		world->sectors[i].index = -1;
		j = -1;
		while (++j < world->sectors[i].objectnum)
		{
			world->sectors[i].objects[j].index = -1;
		}
	}
}

t_bool		init_world(t_world *world)
{
	if (!(world->p_buff = get_buffer(world)))
		return (FALSE);
	init_indexes(world);
}