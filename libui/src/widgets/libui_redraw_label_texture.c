/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_redraw_label_texture.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:33:41 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:55:02 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_redraw_label_texture(t_libui_widget *widget)
{
	SDL_Surface				*tmp;
	t_libui_widget_text		*data;

	if (widget->type == LUI_WT_TEXT)
	{
		data = (t_libui_widget_text *)widget->data;
		tmp = TTF_RenderText_Solid(data->font, data->ptr, data->color);
		if (widget->texture == NULL)
			widget->texture = SDL_CreateRGBSurface(0, widget->rect.w,
				widget->rect.h, 32, 0xFF0000, 0xFF00, 0xFF, 0xFF000000);
		SDL_FillRect(widget->texture, NULL, LIBUI_CLEAR_DEFAULT_COLOR);
		SDL_BlitSurface(tmp, &(SDL_Rect){0, 0, widget->rect.w, widget->rect.h},
						widget->texture, NULL);
		SDL_FreeSurface(tmp);
		widget->need_redraw = 1;
	}
}
