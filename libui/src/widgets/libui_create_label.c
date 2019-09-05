/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_label.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:13:24 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:50:07 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <SDL2/SDL_ttf.h>

int		libui_create_label(t_libui_widget *widget, SDL_Rect size,
	char *text, TTF_Font *font)
{
	t_libui_widget_text	*text_data;
	SDL_Color			default_color;
	SDL_Point			pos;

	*widget = libui_widgets_templates_null();
	widget->type = LUI_WT_TEXT;
	text_data = malloc(sizeof(t_libui_widget_text));
	if (text_data == NULL)
		return (0);
	text_data->ptr = SDL_strdup(text);
	text_data->len = SDL_strlen(text);
	text_data->font = font;
	default_color.a = (LIBUI_LABEL_DEFAULT_COLOR >> 24) & 255;
	default_color.r = (LIBUI_LABEL_DEFAULT_COLOR >> 16) & 255;
	default_color.g = (LIBUI_LABEL_DEFAULT_COLOR >> 8) & 255;
	default_color.b = (LIBUI_LABEL_DEFAULT_COLOR) & 255;
	text_data->color = default_color;
	widget->data = (void *)text_data;
	widget->rect = size;
	pos.x = size.x;
	pos.y = size.y;
	widget->translucid = 1;
	libui_widget_set_pos(widget, pos);
	libui_redraw_label_texture(widget);
	return (1);
}
