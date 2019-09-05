/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_redraw_progressbar_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:54:57 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 22:30:25 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_redraw_progressbar_texture(t_libui_widget *widget)
{
	t_libui_widget_progressbar	*data;
	SDL_Rect					rect;

	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
		data = (t_libui_widget_progressbar *)widget->data;
	else
		return ;
	if (widget->texture == NULL)
		widget->texture = SDL_CreateRGBSurface(0, widget->rect.w,
			widget->rect.h, 32, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);
	rect.x = 0;
	rect.y = 0;
	rect.h = widget->rect.h;
	rect.w = widget->rect.w * (data->value_current - data->value_min)
		/ (data->value_max - data->value_min);
	SDL_FillRect(widget->texture, &rect, data->front_color);
	rect.x = rect.w;
	rect.h = widget->rect.h;
	rect.w = widget->rect.w;
	if (rect.x != rect.w)
		SDL_FillRect(widget->texture, &rect, data->back_color);
	widget->need_redraw = 1;
}
