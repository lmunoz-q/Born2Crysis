/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback_sethover.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:03:54 by tfernand          #+#    #+#             */
/*   Updated: 2019/05/08 16:05:20 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_callback_sethover(t_libui_widget *widget,
	t_libui_callback *callback,
	SDL_EventType filter, void *data)
{
	widget->on_hover.callback = callback;
	widget->on_hover.filter = filter;
	widget->on_hover.user_data = data;
	widget->on_hover.widget = widget;
}
