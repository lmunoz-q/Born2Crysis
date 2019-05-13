/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:29:01 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/13 18:32:27 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

void		handle_key_down(t_input_map *m, SDL_Event *event)
{
	if (event->key.keysym.scancode < KEY_AMOUNT)
	{
		if (m->keys[event->key.keysym.scancode].toggle == TRUE)
			m->keys[event->key.keysym.scancode].active = TRUE;
		m->keys[event->key.keysym.scancode].toggle = FALSE;
	}
}

void		handle_key_up(t_input_map *m, SDL_Event *event)
{
	if (event->key.keysym.scancode < KEY_AMOUNT)
	{
		m->keys[event->key.keysym.scancode].active = FALSE;
		m->keys[event->key.keysym.scancode].toggle = TRUE;
	}
}
