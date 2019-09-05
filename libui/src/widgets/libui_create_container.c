/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_container.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:04:06 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:49:55 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	libui_create_container(t_libui_widget *widget, SDL_Rect rect, int color)
{
	SDL_Rect	rect_tmp;
	SDL_Point	pos;

	*widget = libui_widgets_templates_null();
	widget->type = LUI_WT_COMPOSITE;
	widget->rect = rect;
	pos.x = rect.x;
	pos.y = rect.y;
	libui_widget_set_pos(widget, pos);
	if ((widget->texture = SDL_CreateRGBSurface(0, widget->rect.w,
			widget->rect.h, 32, 0xFF0000, 0xFF00, 0xFF, 0xFF000000)) == NULL)
		return (0);
	rect_tmp.x = 0;
	rect_tmp.y = 0;
	rect_tmp.h = rect.h;
	rect_tmp.w = rect.w;
	if ((color >> 24) != 255)
		widget->translucid = 1;
	SDL_FillRect(widget->texture, &rect_tmp, color);
	widget->need_redraw = 1;
	return (1);
}
