/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:17:35 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/14 14:20:02 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void editor_render(t_e *e, t_editor_interface			*editor_interface)
{
	mf_memset(get_zbuff(), 0, e->win->surface->w * e->win->surface->h * sizeof(double));
	remplir_preview(editor_interface, e);
	libui_window_update(e->win);
	libui_window_title(e->win, "fps: %d", e->win->fps);
	libui_window_refresh(e->win);
}

