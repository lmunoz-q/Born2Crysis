/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:07:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 22:00:04 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	run_game(t_e *e)
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
