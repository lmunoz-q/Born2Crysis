/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback_hoverbutton.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:30:53 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:24:13 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int		libui_callback_hoverbutton(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	SDL_Rect		rect_tmp;
	SDL_Cursor		*cursor;

	if (widget == NULL)
		return (0);
	(void)event;
	rect_tmp.x = 0;
	rect_tmp.y = 0;
	rect_tmp.h = widget->rect.h;
	rect_tmp.w = widget->rect.w;
	if (widget->is_hover)
	{
		cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		SDL_FillRect(widget->texture, &rect_tmp,
						((t_libui_double_color *)data)->first_color);
	}
	else
	{
		cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		SDL_FillRect(widget->texture, &rect_tmp,
						((t_libui_double_color *)data)->second_color);
	}
	SDL_SetCursor(cursor);
	widget->need_redraw |= 1;
	return (1);
}
