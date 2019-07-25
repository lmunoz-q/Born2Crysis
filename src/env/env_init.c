/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:24:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/07/25 10:21:01 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

t_bool		env_init(t_e *e)
{
	t_libui_window_constructor constructor;
	constructor = libui_window_default_constructor();
	constructor.rect.h = 900;
	constructor.rect.w = 1600;
	//constructor.winow_flags |= SDL_WINDOW_FULLSCREEN;
	
	if (!(e->win = libui_window_create(constructor, NULL, NULL, NULL)))
		return (FALSE);
	init_zbuff(e->win->surface->w * e->win->surface->h);
	init_camera(&e->camera, (t_vec2i){.x = e->win->surface->w, .y = e->win->surface->h});
	init_input_map(&e->input_map, e->win);
	init_default_controls(&e->input_map, e);
	init_player(&e->main_player);
	e->thread[B2C_THREAD_CLIENT] = NULL;
	e->thread[B2C_THREAD_GRAPHIC] = NULL;
	e->thread[B2C_THREAD_SERVER] = NULL;
	e->game_running = TRUE;
	e->stats.fps = 0;
	return (TRUE);
}
