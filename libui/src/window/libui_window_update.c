/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_update.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:13:45 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 20:00:37 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_window_update(t_libui_window *win)
{
	t_libui_widgets_surface *tmp;

	libui_window_clear_atomic(win);
	tmp = win->widgets_surface;
	while (tmp != NULL)
	{
		libui_widgets_draw(win->widgets_surface);
		SDL_BlitScaled(tmp->surface, NULL, win->surface, NULL);
		tmp = tmp->next;
	}
	libui_window_refresh(win);
}
