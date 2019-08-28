/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:31:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/28 17:19:14 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_bool	init_game_state(t_e *e)
{
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1",
		SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//SDL_SetWindowFullscreen(e->win->ptr, SDL_WINDOW_FULLSCREEN);
	gthread_init(28, e->win->surface, get_polygon_buffer(), GTHREAD_GAME);
	gthread_get(GTHREAD_GAME);
	return (TRUE);
}
