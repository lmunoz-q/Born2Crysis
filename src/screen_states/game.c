/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 11:07:16 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/08 11:53:54 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	run_game(t_e *e)
{
	uint32_t	last_frame;
	double		elapsed_time;
	(void)e;
	
	elapsed_time = 0;
	last_frame = SDL_GetTicks();
	while (TRUE)
	{
		while (elapsed_time >= DELTATIME)
		{
			//input
			//"logic"
			elapsed_time -= DELTATIME;
		}
		//render
		printf("lel\n");
	}
}
