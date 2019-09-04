/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endscreen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:16:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/09/04 17:26:12 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	init_endscreen(t_e *e)
{
	
}

void		run_end_screen(t_e	*e)
{
	uint32_t	last_frame;
	double		elapsed_time;
	uint32_t	tmp;

	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (e->endscreen_running)
	{
		while (elapsed_time >= DELTATIME)
		{
			handle_events(&e->input_map);
			//update(e);
			libui_window_title(e->win, "FPS: %d", e->stats.fps);
			elapsed_time -= DELTATIME;
		}
		//render(e);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
}