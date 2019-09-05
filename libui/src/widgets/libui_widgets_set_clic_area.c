/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_set_clic_area.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:58:32 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:58:37 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets.h>

void					libui_widgets_set_clic_area(t_libui_widgets_surface *ws,
												t_libui_widget *w)
{
	int				x;
	int				y;

	if (ws == NULL || w->is_hiden)
		return ;
	y = w->rect.y - 1;
	if (w->translucid && w->texture != NULL)
		while (++y < w->rect.y + w->rect.h)
		{
			x = w->rect.x - 1;
			while (++x < w->rect.x + w->rect.w)
				if (((t_libui_pixel_color)((Uint32*)w->texture->pixels)[x
				- w->rect.x + (y - w->rect.y) * w->rect.w]).c.a
				&& ws->pixel_bound_widget[x + y * ws->surface->w] == w->parent)
					ws->pixel_bound_widget[x + y * ws->surface->w] = w;
		}
	else
		while (++y < w->rect.y + w->rect.h)
		{
			x = w->rect.x - 1;
			while (++x < w->rect.x + w->rect.w)
				if (ws->pixel_bound_widget[x + y * ws->surface->w] == w->parent)
					ws->pixel_bound_widget[x + y * ws->surface->w] = w;
		}
}
