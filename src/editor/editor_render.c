/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:17:35 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/18 21:17:34 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	editor_render(t_e *e, t_libui_widgets_surface *ws,
	t_editor_interface *editor_interface)
{
	mf_memset(ws->surface->pixels, 0,
		e->win->surface->pitch * e->win->surface->h);
	editor_interface->editor_cam.view_dir = e->input_map.mouse.front;
	remplir_preview(editor_interface, e);
	remplir_3dview(editor_interface, e);
	mf_memset(get_zbuff(), 0,
		e->win->surface->w * e->win->surface->h * sizeof(double));
	libui_window_update(e->win);
}
