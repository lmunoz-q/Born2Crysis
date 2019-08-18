/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:29:01 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/18 13:42:28 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

void		handle_key_down(t_input_map *m, SDL_Event *event)
{
	if (event->type == SDL_KEYDOWN && event->key.keysym.scancode < KEY_AMOUNT)
	{
		if (m->keys[event->key.keysym.scancode].toggle == TRUE)
			m->keys[event->key.keysym.scancode].active = TRUE;
		m->keys[event->key.keysym.scancode].toggle = FALSE;
	}
	else if (event->button.which < BUTTON_AMOUNT)
	{
		if (m->buttons[event->button.which].toggle == TRUE)
			m->buttons[event->button.which].active = TRUE;
		m->buttons[event->button.which].toggle = FALSE;
		if (event->type == SDL_MOUSEWHEEL)
			m->mouse.wheel_scrol = (t_vec2i){.n.x = event->wheel.x, .n.y = event->wheel.y};
	}
}

void		handle_key_up(t_input_map *m, SDL_Event *event)
{
	if (event->type == SDL_KEYUP && event->key.keysym.scancode < KEY_AMOUNT)
	{
		m->keys[event->key.keysym.scancode].active = FALSE;
		m->keys[event->key.keysym.scancode].toggle = TRUE;
	}
	else if (event->button.which < BUTTON_AMOUNT)
	{
		m->buttons[event->button.which].active = FALSE;
		m->buttons[event->button.which].toggle = TRUE;
		if (event->type == SDL_MOUSEWHEEL)
			m->mouse.wheel_scrol = (t_vec2i){.n.x = event->wheel.x, .n.y = event->wheel.y};
	}
}
