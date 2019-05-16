/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 18:09:08 by mfischer          #+#    #+#             */
/*   Updated: 2019/05/16 15:15:50 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handler.h"

static void		init_keys(t_input_map	*m)
{
	int i;

	i = -1;
	while (++i < KEY_AMOUNT)
	{
		m->keys[i].toggle = TRUE;
		m->keys[i].func = NULL;
		m->keys[i].params = NULL;
		m->keys[i].active = FALSE;
		m->keys[i].continuous = TRUE;
	}
}

static void		init_buttons(t_input_map *m)
{
	int i;

	i = -1;
	while (++i < BUTTON_AMOUNT)
	{
		m->buttons[i].toggle = TRUE;
		m->buttons[i].func = NULL;
		m->buttons[i].params = NULL;
		m->buttons[i].active = FALSE;
		m->buttons[i].continuous = TRUE;
	}
}

static void		init_mouse(t_mouse *m, t_libui_window *win)
{
	m->win = win;
	m->pos = (t_vec2i){.x = win->surface->w / 2, .y = win->surface->h / 2};
	m->sensitivity = (t_vec2d){.x = DEFAULT_MOUSE_SENSITIVITY, .y = DEFAULT_MOUSE_SENSITIVITY};
	vec3_clear(m->front);
	m->front[2] = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void			init_input_map(t_input_map	*ip, t_libui_window *win)
{
	init_keys(ip);
	init_buttons(ip);
	init_mouse(&ip->mouse, win);
}
