/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:07:16 by mfischer          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/07/09 15:01:33 by mfischer         ###   ########.fr       */
=======
/*   Updated: 2019/07/09 10:06:23 by mfischer         ###   ########.fr       */
>>>>>>> e25627bb90903973bbf1c4b16c02989e5c14161c
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

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
			printf("fps = %i\n", e->stats.fps);
			elapsed_time -= DELTATIME;
		}
		render(e);
		tmp = SDL_GetTicks();
		elapsed_time += (double)(tmp - last_frame) / 1000.0;
		last_frame = tmp;
		count_fps(&e->stats.fps);
	}
}
