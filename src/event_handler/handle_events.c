/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 17:33:20 by mfischer          #+#    #+#             */
/*   Updated: 2019/08/20 14:12:00 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom_nukem.h>

static void		handle_inputs(t_input_map *m)
{
	int		i;

	i = -1;
	while (++i < KEY_AMOUNT)
		if (m->keys[i].active == TRUE)
		{
			if (m->keys[i].func != NULL)
				m->keys[i].func(m->keys[i].params);
			if (!m->keys[i].continuous)
				m->keys[i].active = FALSE;
		}
	i = -1;
	while (++i < BUTTON_AMOUNT)
		if (m->buttons[i].active == TRUE)
		{
			if (m->buttons[i].func != NULL)
				m->buttons[i].func(m->buttons[i].params);
			if (!m->buttons[i].continuous)
				m->buttons[i].active = FALSE;
		}
}

void			handle_events(t_e *e)
{
	SDL_Event	event;

	while (libui_process_events(&event))
	{
		if (event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN)
			handle_key_down(&e->input_map, &event);
		if (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP)
			handle_key_up(&e->input_map, &event);
		if (event.type == SDL_QUIT)
			e->input_map.keys[SDL_SCANCODE_ESCAPE].active = TRUE;
		if (event.type == SDL_MOUSEMOTION)
			handle_mouse_motion(&e->input_map.mouse, &event, e);
		if (event.type == SDL_MOUSEWHEEL)
		{
			e->input_map.mouse.wheel_scrol = (t_vec2i){.n.x = event.wheel.x,
				.n.y = event.wheel.y};
			e->input_map.buttons[KF_MOUSEWHEEL].active = TRUE;
		}
		if (event.type == SDL_DROPFILE)
		{
			e->input_map.drop_file_path = event.drop.file;
			e->input_map.keys[KF_FILEDROP].active = TRUE;
		}
	}
	handle_inputs(&e->input_map);
}
