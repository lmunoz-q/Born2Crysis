/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endscreen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:16:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 19:03:39 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	init_endscreen(t_e *e)
{
	e->endscreen = mesh_create((t_vec2i){.a = {100, 100}});
	if (!e->endscreen)
		e->endscreen_running = FALSE;
	else
	{
		e->endscreen->matrix = mat4_rotate_roll(e->endscreen->matrix, 180);
		e->endscreen->matrix = mat4_translate(e->endscreen->matrix, 0, -20, 0);
	}
	
}

void		run_end_screen(t_e	*e)
{
	uint32_t	last_frame;
	double		elapsed_time;
	uint32_t	tmp;

	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	init_endscreen(e);
	while (e->endscreen_running)
	{
		while (elapsed_time >= DELTATIME)
		{
			handle_events(&e->input_map);
			//update(e);
			libui_window_title(e->win, "FPS: %d", e->stats.fps);
			elapsed_time -= DELTATIME;
		}
		render_endscreen(e);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
}