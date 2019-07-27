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

void			update_player_sector(t_player *p, t_world *world)
{
	int			i;
	t_sector	*sector;

	sector = get_sector(p->sector, world);
	i = -1;
	while (++i < sector->meshnum)
	{
		if (sector->mesh[i].sector_id == -1 || !sector->mesh[i].polygonnum)
			continue ;
		if (vec3_dot(/*vec3_normalize(*/vec3vec3_substract(sector->mesh[i].polygons[0].v01.vec3d, p->pos)/*)*/, sector->mesh[i].portal_normal) > 0.0)
		{
			p->sector = sector->mesh[i].sector_id;
			return ;
		}
	}
}
