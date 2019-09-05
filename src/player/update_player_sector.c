/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player_sector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 23:01:46 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/29 19:40:52 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	iupdate_entity_sector(t_eidos_frame *e, t_world *world, t_mesh *mesh)
{
	t_sector	*tmp;

	if (vec3_dot(vec3vec3_substract(mat4vec4_multiply(mesh->matrix,
		mesh->polygons[0].v01).c3.vec3d, e->position),
			mesh->portal_normal) > 0.0)
	{
		if (e->sector->id != mesh->sector_id)
		{
			if (e->sector->physics.leaving_effect.id != -1)
				apply_effect(e->sector->physics.leaving_effect, e->sector);
			if ((tmp = get_sector(mesh->sector_id,
					world))->physics.entering_effect.id != -1)
				apply_effect(e->sector->physics.entering_effect, e->sector);
		}
		e->sector = get_sector(mesh->sector_id, world);
		return ;
	}
}

void	update_entity_sector(t_eidos_frame *e, t_world *world)
{
	int32_t		i;
	t_mesh		*mesh;

	i = -1;
	if (!e->sector)
		return ;
	while (++i < e->sector->meshnum)
	{
		mesh = &e->sector->mesh[i];
		if (mesh->sector_id == -1 || !mesh->polygonnum)
			continue ;
		iupdate_entity_sector(e, world, mesh);
	}
}
