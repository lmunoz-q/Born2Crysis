/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_editor_interface.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/07/20 16:13:16 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom-nukem.h"

void	launch_editor_interface(t_e *e)
{
	t_libui_widgets_surface		ws;
	TTF_Font *					font;
	SDL_Event					event;

	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		&ws);
	e->win->widgets_surface = &ws;
	e->win->refresh_rate = 60;
	font = TTF_OpenFont("./libui/resources/Prototype.ttf", 64);
	if (font == NULL)
	{
		printf("Unable to load the font\n");
	}
	else
	{
	}
	while (1)
	{
		if (libui_process_events(&event))
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break;
		}
	}
	TTF_CloseFont(font);
}
