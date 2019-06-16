/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:24:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/14 12:57:51 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

t_bool		env_init(t_e *e)
{
	t_libui_window_constructor constructor;
	constructor = libui_window_default_constructor();
	constructor.rect.h = 900;
	constructor.rect.w = 1600;
	if (!(e->win = libui_window_create(constructor, NULL, NULL, NULL)))
		return (FALSE);
	init_camera(&e->camera, (t_vec2i){.x = e->win->surface->w, .y = e->win->surface->h});
	init_input_map(&e->input_map, e->win);
	init_default_controls(&e->input_map, e);
	init_player(&e->main_player);
	set_thread_pool(16, 5000);
	e->thread[B2C_THREAD_CLIENT] = NULL;
	e->thread[B2C_THREAD_GRAPHIC] = NULL;
	e->thread[B2C_THREAD_SERVER] = NULL;
	e->game_running = TRUE;
	e->stats.fps = 0;
	return (TRUE);
}
