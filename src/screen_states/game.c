/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:07:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/01 17:16:42 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		run_game(t_e *e)
{
	uint32_t	last_frame;
	double		elapsed_time;
	uint32_t	tmp;

	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (e->game_running)
	{
		while (elapsed_time >= DELTATIME)
		{
			handle_events(&e->input_map);
			update(e);
			libui_window_title(e->win, "FPS: %d", e->stats.fps);
			elapsed_time -= DELTATIME;
		}
		render(e);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
	gthread_destroy(gthread_get(GTHREAD_LAST));
}
