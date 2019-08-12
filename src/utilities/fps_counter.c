/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:36:47 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/08 12:46:38 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void		count_fps(int *res)
{
	static uint32_t	last_frame;
	static int		fps_count;

	fps_count = 0;
	last_frame = 0;
	if (!last_frame)
	{
		last_frame = SDL_GetTicks();
	}
	fps_count++;
	if (SDL_GetTicks() - last_frame >= 1000)
	{
		*res = fps_count;
		fps_count = 0;
		last_frame = SDL_GetTicks();
	}
}
