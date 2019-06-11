/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 23:33:23 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 20:34:08 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_sector(	t_sector *sector, t_camera *cam, SDL_Surface *surface)
{
	int i;

	i = -1;
	while (++i < sector->meshnum)
		render_mesh(&sector->mesh[i], cam, surface);
 	i = -1;
	while (++i < sector->objectnum)
		render_mesh(sector->objects[i].mesh, cam, surface);
	//HANDLE PORTALS

}
