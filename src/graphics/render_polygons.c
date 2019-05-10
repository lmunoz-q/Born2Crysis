/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_polygons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 00:03:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/11 00:11:54 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_polygons(t_polygonlist *plist, double m2wmat[4][4],
							t_libui_window *win, t_camera *cam)
{
	model_to_world(plist, m2wmat);
	cull_backfaces(plist, cam->pos);
	world_to_view(plist, cam->view_matrix);
	view_to_projection(plist, cam->projection_matrix, (t_vec2i){.x = win->surface->w, .y = win->surface->h});
	//clip funcs
	rasterize(plist, win);
	purge_clipped_polygons(plist);
}