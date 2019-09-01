/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:10:00 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 18:10:02 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

int		change_color(SDL_Event *event, t_libui_widget *widget, void *data)
{
	SDL_Rect		rect_tmp;
	SDL_Cursor		*cursor;

	if (event->type == SDL_MOUSEMOTION)
	{
		rect_tmp.x = 0;
		rect_tmp.y = 0;
		rect_tmp.h = widget->rect.h;
		rect_tmp.w = widget->rect.w;
		if (widget->is_hover)
		{
			cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			SDL_FillRect(widget->texture, &rect_tmp,
				((t_double_color *)data)->first_color);
		}
		else
		{
			cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			SDL_FillRect(widget->texture, &rect_tmp,
				((t_double_color *)data)->second_color);
		}
		SDL_SetCursor(cursor);
		widget->need_redraw = 1;
	}
	return (1);
}
