/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_polygons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 00:03:30 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/11 16:51:55 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void		render_polygons(t_polygonlist *plist, double m2wmat[4][4],
							t_libui_window *win, t_camera *cam)
{
	model_to_world(plist, m2wmat);
	cull_backfaces(plist, cam->pos);printf("%f, %f, %f, %f\n", ((t_polygon *)plist->list)->v01[0],((t_polygon *)plist->list)->v01[1], ((t_polygon *)plist->list)->v01[2], ((t_polygon *)plist->list)->v01[3]);
	world_to_view(plist, cam->view_matrix);printf("%f, %f, %f, %f\n", ((t_polygon *)plist->list)->v01[0],((t_polygon *)plist->list)->v01[1], ((t_polygon *)plist->list)->v01[2], ((t_polygon *)plist->list)->v01[3]);
	clip_znear(plist);
	view_to_projection(plist, cam->projection_matrix, (t_vec2i){.x = win->surface->w, .y = win->surface->h});
	//clip funcs
	clip_polygons_2d(plist, (t_vec2i){.x = win->surface->w, .y = win->surface->h});
	rasterize(plist, win);
	purge_clipped_polygons(plist);
}
