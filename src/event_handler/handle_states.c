/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:29:01 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 13:51:13 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

void		handle_key_down(t_input_map *m, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (m->keys[event->key.keysym.scancode].toggle == TRUE)
			m->keys[event->key.keysym.scancode].active = TRUE;
		m->keys[event->key.keysym.scancode].toggle = FALSE;
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button < BUTTON_AMOUNT)
	{
		if (m->buttons[event->button.button].toggle == TRUE)
			m->buttons[event->button.button].active = TRUE;
		m->buttons[event->button.button].toggle = FALSE;
	}
}

void		handle_key_up(t_input_map *m, SDL_Event *event)
{
	if (event->type == SDL_KEYUP)
	{
		m->keys[event->key.keysym.scancode].active = FALSE;
		m->keys[event->key.keysym.scancode].toggle = TRUE;
	}
	else if (event->type == SDL_MOUSEBUTTONUP && event->button.button < BUTTON_AMOUNT)
	{
		m->buttons[event->button.button].active = FALSE;
		m->buttons[event->button.button].toggle = TRUE;
	}
}
