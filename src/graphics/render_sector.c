/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:33:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/02 18:37:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_sector(t_sector *sector, t_camera *cam,
	SDL_Surface *surface, t_mesh *portal)
{
	static short	protec = 0;
	int32_t			i;
	t_sector		*next_sect;

	if (!sector || !cam || !surface)
		return ;
	if (portal == NULL)
		protec = 0;
	if (protec >= MAX_SECTORS)
	{
		while (sector_queue_pop());
		return ;
	}
	protec++;
	i = -1;
	if (portal)
		portal_cull(sector->mesh, sector->meshnum, portal,
			(t_vec4d){.c3 = {.vec3d = cam->pos}});
	while (++i < sector->meshnum)
		if (!portal || sector->mesh[i].active)
			render_mesh(&sector->mesh[i], cam, surface, &sector->lights);
	while ((next_sect = sector_queue_pop()))
		render_sector(next_sect, cam, surface, next_sect->src_portal);
	
}
