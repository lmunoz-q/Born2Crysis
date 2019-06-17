/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 23:43:13 by mfischer          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/17 13:45:36 by mfischer         ###   ########.fr       */
=======
/*   Updated: 2019/06/17 15:21:45 by mfischer         ###   ########.fr       */
>>>>>>> dev
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_mesh(t_mesh *mesh, t_camera *cam, SDL_Surface *surface, t_light_comp *lcomp)
{
	int			count;
	t_polygon	*p;

	p = get_polygon_buffer();
	count = model_to_world(mesh, cam->pos, p);
	calculate_lighting(p, count, lcomp);
	world_to_view(p, count, cam->view_matrix);
	count = clip_znear(p, count);
	view_to_projection(p, count, cam->projection_matrix, surface);
	count = portal_clip(p, count, surface->w, surface->h);
	rasterize(p, count, surface);
}
