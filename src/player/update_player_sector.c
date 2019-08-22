/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_sector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 23:01:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/22 20:49:33 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void			update_entity_sector(t_entity *e, t_world *world)
{
	Uint32		i;
	t_sector	*tmp;
	t_mesh		*mesh;

	i = (Uint32)-1;
	if (!e->sector)
		return ;
	while (++i < e->sector->meshnum)
	{
		mesh = &e->sector->mesh[i];
		if (mesh->sector_id == (Uint32)-1 || !mesh->polygonnum)
			continue ;
		if (vec3_dot(vec3vec3_substract(mesh->polygons[0].v01.c3.vec3d
			, e->position), mesh->portal_normal) > 0.0)
		{
			if (e->sector->id != mesh->sector_id)
			{
				if (e->sector->physics.leaving_effect != EFF_NOTHING)
					apply_effect(e, world, e->sector->physics.leaving_effect);
				if ((tmp = get_sector(mesh->sector_id,
						world))->physics.entering_effet != EFF_NOTHING)
					apply_effect(e, world, tmp->physics.entering_effet);
			}
			e->sector = get_sector(mesh->sector_id, world);
			return ;
		}
	}
}
