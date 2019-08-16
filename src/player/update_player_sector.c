/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_sector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 23:01:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/02 18:04:26 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void			update_entity_sector(t_entity *e, t_world *world)
{
	int			i;
	t_sector	*sector;
	t_sector	*tmp;

	sector = get_sector(e->sector, world);
	i = -1;
	while (++i < sector->meshnum)
	{
		if (sector->mesh[i].sector_id == -1 || !sector->mesh[i].polygonnum)
			continue ;
		if (vec3_dot(vec3vec3_substract(sector->mesh[i].polygons[0].v01.c3.vec3d
			, e->position), sector->mesh[i].portal_normal) > 0.0)
		{
			if (e->sector != sector->mesh[i].sector_id)
			{
				if (sector->physics.leaving_effect != EFF_NOTHING)
					apply_effect(e, world, sector->physics.leaving_effect);
				if ((tmp = get_sector(sector->mesh[i].sector_id,
						world))->physics.entering_effet != EFF_NOTHING)
					apply_effect(e, world, tmp->physics.entering_effet);
			}
			e->sector = sector->mesh[i].sector_id;
			return ;
		}
	}
}
