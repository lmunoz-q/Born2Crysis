/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_slider.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 23:24:57 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 22:40:11 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static int	slider_on_press(SDL_Event *event, t_libui_widget *widget,
	void *data)
{
	t_libui_widget_progressbar		*progressdata;
	int								tmp_x;

	(void)event;
	(void)data;
	if (widget->type == LUI_WT_SLIDER)
	{
		progressdata = (t_libui_widget_progressbar *)widget->data;
		SDL_GetMouseState(&tmp_x, NULL);
		tmp_x = tmp_x - widget->rect.x;
		if (tmp_x > widget->rect.w)
			tmp_x = widget->rect.w;
		if (widget->rect.w == 0)
			return (-1);
		tmp_x = (double)(tmp_x) / (double)widget->rect.w
				* (double)(progressdata->value_max - progressdata->value_min);
		libui_progressbar_set_current_value(widget, tmp_x);
	}
	return (0);
}

static void	init_slider(t_libui_widget *widget)
{
	widget->type = LUI_WT_SLIDER;
	widget->on_press.callback = slider_on_press;
	widget->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget->on_press.user_data = NULL;
	widget->on_press.widget = widget;
}

int			libui_create_slider(t_libui_widget *widget, SDL_Rect rect,
	SDL_bool with_cursor)
{
	(void)with_cursor;
	if (!(libui_create_progressbar(widget, rect)))
	{
		return (0);
	}
	init_slider(widget);
	return (1);
}
