/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:31:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/12 15:52:18 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

t_bool	init_game_state(t_e *e)
{
	skybox_load(&e->world, "assets/skybox/skybox2.bmp");
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1",
		SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	gthread_init(32, e->win->surface, get_polygon_buffer());
	return (TRUE);
}
