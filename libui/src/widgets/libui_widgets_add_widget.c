/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_add_widget.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:57:36 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:58:01 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets.h>
#include "libui.h"

static inline void	i_0(t_libui_widgets_surface *ws,
						t_libui_widget *widget,
						t_libui_widget_add_flags flags,
						t_libui_widget *parent)
{
	if (parent != NULL && !libui_sdl_rect_is_inside(widget->rect, parent->rect))
		parent = NULL;
	if (parent != NULL)
	{
		if (parent->shilds != NULL)
			widget->next = parent->shilds;
		parent->shilds = widget;
	}
	else if (ws != NULL)
	{
		widget->next = ws->widgets;
		ws->widgets = widget;
	}
	widget->parent = parent;
	if (flags & LUI_WAF_TRANSLUCID)
		widget->translucid = 1;
	if (ws != NULL)
		libui_widgets_set_clic_area(ws, widget);
	widget->ws = ws;
}

int					libui_widgets_add_widget(t_libui_widgets_surface *ws,
												t_libui_widget *widget,
												t_libui_widget_add_flags flags,
												t_libui_widget *parent)
{
	SDL_Point pos;

	widget->parent = parent;
	pos.x = widget->relative_pos.x;
	pos.y = widget->relative_pos.y;
	libui_widget_set_pos(widget, pos);
	if (ws != NULL)
	{
		if (!libui_sdl_rect_is_inside(widget->rect,
				(SDL_Rect){0, 0, ws->surface->w, ws->surface->h}))
			return (-1);
		if (flags & LUI_WAF_SHILD && parent == NULL)
			parent = ws->pixel_bound_widget[widget->rect.x
			+ widget->rect.y * ws->surface->w];
	}
	i_0(ws, widget, flags, parent);
	return (0);
}
