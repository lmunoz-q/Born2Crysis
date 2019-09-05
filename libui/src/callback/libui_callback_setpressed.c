/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback_setpressed.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:05:50 by tfernand          #+#    #+#             */
/*   Updated: 2019/05/08 16:05:53 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_callback_setpressed(t_libui_widget *widget,
	t_libui_callback *callback,
	SDL_EventType filter, void *data)
{
	widget->on_press.callback = callback;
	widget->on_press.filter = filter;
	widget->on_press.user_data = data;
	widget->on_press.widget = widget;
}
