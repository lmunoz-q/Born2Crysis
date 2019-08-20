/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:33:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 15:59:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_sector(t_sector *sector, t_camera *cam, SDL_Surface *surface, t_mesh *portal)
{
	int			i;
	t_sector	*next_sect;

	i = -1;
	if (portal)
		portal_cull(sector->mesh, sector->meshnum, portal, (t_vec4d){.c3 = {.vec3d = cam->pos}});
	while (++i < sector->meshnum)
	{
		if (!portal || sector->mesh[i].active)
			render_mesh(&sector->mesh[i], cam, surface, &sector->lights);
	}
	
	while ((next_sect = sector_queue_pop()))
		render_sector(next_sect, cam, surface, next_sect->src_portal);
}
