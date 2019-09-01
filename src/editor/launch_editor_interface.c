/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/31 16:31:15 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"

void	close_editor(t_editor_interface *editor_interface)
{
	free_editor_interface(editor_interface);
	TTF_CloseFont(editor_interface->font);
}

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface	ws;
	uint32_t				last_frame;
	double					elapsed_time;
	uint32_t				tmp;

	if (!init_editor(e, &ws, &e->editor))
	{
		elapsed_time = 0;
		last_frame = SDL_GetTicks();
		while (e->editor_running)
		{
			while (elapsed_time >= DELTATIME)
			{
				editor_event(e);
				editor_update(e, &e->editor);
				elapsed_time -= DELTATIME;
			}
			editor_render(e, &ws, &e->editor);
			tmp = SDL_GetTicks();
			elapsed_time += (double)(tmp - last_frame) / 1000.0;
			last_frame = tmp;
			count_fps(&e->stats.fps);
		}
	}
	close_editor(&e->editor);
}
