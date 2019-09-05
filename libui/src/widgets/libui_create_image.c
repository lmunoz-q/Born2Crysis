/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_image.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:58:27 by tfernand          #+#    #+#             */
/*   Updated: 2019/04/05 16:33:41 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int		libui_create_image(t_libui_widget *widget, char *path, SDL_Rect rect)
{
	SDL_Point	pos;

	*widget = libui_widgets_templates_null();
	if ((widget->texture = libui_surface_image_load_32argb(path,
		rect.w, rect.h)) == NULL)
		return (0);
	widget->type = LUI_WT_IMAGE;
	widget->rect = rect;
	pos.x = rect.x;
	pos.y = rect.y;
	libui_widget_set_pos(widget, pos);
	widget->need_redraw = 1;
	return (1);
}
