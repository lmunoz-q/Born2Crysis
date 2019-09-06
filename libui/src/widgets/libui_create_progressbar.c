/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_progressbar.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:32:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:50:18 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	libui_create_progressbar(t_libui_widget *widget, SDL_Rect rect)
{
	t_libui_widget_progressbar		*pgrb;
	SDL_Point						pos;

	*widget = libui_widgets_templates_null();
	widget->type = LUI_WT_PROGRESSBAR;
	widget->rect = rect;
	pos.x = rect.x;
	pos.y = rect.y;
	libui_widget_set_pos(widget, pos);
	pgrb = (t_libui_widget_progressbar *)
		malloc(sizeof(t_libui_widget_progressbar));
	if (pgrb == NULL)
		return (0);
	pgrb->back_color = LIBUI_WIDGET_PROGRESSBAR_DEFAULT_BACKCOLOR;
	pgrb->front_color = LIBUI_WIDGET_PROGRESSBAR_DEFAULT_FRONTCOLOR;
	pgrb->value_min = 0;
	pgrb->value_max = 100;
	pgrb->value_current = 50;
	widget->data = (void*)pgrb;
	libui_redraw_progressbar_texture(widget);
	return (1);
}
