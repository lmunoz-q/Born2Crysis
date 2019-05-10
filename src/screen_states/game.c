/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:07:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/10 22:38:58 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	run_game(t_e *e)
{
	uint32_t	last_frame;
	double		elapsed_time;
	SDL_Event	event;
	(void)e;

	uint32_t	tmp = 0;
	
	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (e->game_running)
	{
		
		while (elapsed_time >= DELTATIME)
		{
			//input
			while (libui_process_events(&event))
			{
				if (event.type == SDL_QUIT
					|| (event.type == SDL_KEYDOWN
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
					e->game_running = FALSE;
			}
			//"logic"
			//printf("fps = %i\n", e->stats.fps);
			elapsed_time -= DELTATIME;
		}
		//render
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
}
