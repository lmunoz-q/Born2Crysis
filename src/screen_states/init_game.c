/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:31:43 by mfischer          #+#    #+#             */
/*   Updated: 2019/06/10 23:42:43 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

t_bool	init_game_state(t_e *e)
{
	if (!(init_world(&e->world)))
		return (FALSE);
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1",
		SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);	
	return (TRUE);
}
