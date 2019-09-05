/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widget_set_visibility.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:57:28 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:57:33 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets.h>

static inline void	i_paint(t_libui_widgets_surface *ws, SDL_Rect rect,
	t_libui_widget *paint, t_libui_widget *target)
{
	int	x;
	int	y;

	y = rect.y - 1;
	if (paint != NULL && paint->translucid && paint->texture != NULL)
		while (++y < rect.y + rect.h)
		{
			x = rect.x - 1;
			while (++x < rect.x + rect.w)
				if (ws->pixel_bound_widget[x + y * ws->surface->w] == target)
					if (((t_libui_pixel_color*)paint->texture->pixels)[(x
								- rect.x) + (y - rect.y) * paint->rect.w].c.a)
						ws->pixel_bound_widget[x + y * ws->surface->w] = paint;
		}
	else
		while (++y < rect.y + rect.h)
		{
			x = rect.x - 1;
			while (++x < rect.x + rect.w)
				if (ws->pixel_bound_widget[x + y * ws->surface->w] == target)
					ws->pixel_bound_widget[x + y * ws->surface->w] = paint;
		}
}

void				libui_widget_set_visibility(t_libui_widget *widget,
												int state,
												int inherit,
												int brothers)
{
	t_libui_widget	*paint;
	t_libui_widget	*target;

	if (state)
	{
		widget->is_hiden = 0;
		widget->need_redraw |= 1;
		paint = widget;
		target = widget->parent;
	}
	else
	{
		widget->is_hiden = 1;
		paint = widget->parent;
		target = widget;
		if (paint != NULL)
			paint->need_redraw |= 1;
	}
	i_paint(widget->ws, widget->rect, paint, target);
	if (widget->shilds != NULL)
		libui_widget_set_visibility(widget->shilds, inherit ? state
			: !widget->shilds->is_hiden, inherit, 1);
	if (brothers && widget->next != NULL)
		libui_widget_set_visibility(widget->next, inherit ? state
			: !widget->next->is_hiden, inherit, 1);
}
