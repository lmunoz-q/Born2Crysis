/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 10:24:42 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/27 14:10:46 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	constructor.rect.h = 1080;
**	constructor.rect.w = 1920;
*/

t_bool							env_init(t_e *e)
{
	t_libui_window_constructor	constructor;

	constructor = libui_window_default_constructor();
//	constructor.rect.h = 1080;
	constructor.rect.h = 720;
//	constructor.rect.w = 1920;
	constructor.rect.w = 1280;
	constructor.winow_flags |= SDL_WINDOW_SHOWN;
	if (!(e->win = libui_window_create(constructor, NULL, NULL, NULL)))
		return (FALSE);
	init_zbuff(constructor.rect.h * constructor.rect.w);
	init_camera(&e->camera, (t_vec2i){.n = {.x = e->win->surface->w,
		.y = e->win->surface->h}});
	init_input_map(&e->input_map, e->win);
	init_default_controls(&e->input_map, e);
	e->thread[B2C_THREAD_CLIENT] = NULL;
	e->thread[B2C_THREAD_GRAPHIC] = NULL;
	e->thread[B2C_THREAD_SERVER] = NULL;
	e->game_running = TRUE;
	e->stats.win = FALSE;
	e->stats.fps = 0;
	return (TRUE);
}
