/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 00:24:25 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 19:25:56 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_sector(t_sector *sector, t_libui_window *win, t_camera *cam)
{
	int i;

	i = -1;
	while (++i < sector->objectnum)
		render_object(cam, win, &sector->objects[i]);
	i = -1;
	while (++i < (int)sector->surfacenum)
		if (sector->surfaces[i].next_sector_id == -1)
			render_polygons(sector->surfaces[i].polygons,
							sector->surfaces[i].matrix, win, cam);
		//else render next sector but only objects visible...
}
