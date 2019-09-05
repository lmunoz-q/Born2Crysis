/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_textbutton.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:48:29 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 18:41:31 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int		libui_create_textbutton(t_libui_widget *widget,
							t_libui_textbutton_constructor *constructor)
{
	t_libui_widget *widget_label;

	if (!libui_create_button(widget, constructor->rect, 0xff999999))
	{
		mf_printf("Unable to create the button\n");
		return (-1);
	}
	widget->type = LUI_WT_TEXT_BUTTON;
	libui_callback_sethover(widget, libui_callback_hoverbutton, SDL_MOUSEMOTION,
							(void *)(constructor->theme));
	if (!(widget_label = malloc(sizeof(t_libui_widget))))
	{
		mf_printf("Malloc error\n");
		return (-1);
	}
	if (!libui_create_label(widget_label, constructor->label_rect,
							constructor->text, constructor->font))
	{
		mf_printf("Unable to create the label\n");
		return (-1);
	}
	libui_widgets_add_widget(constructor->ws, widget, 0, constructor->parent);
	libui_widgets_add_widget(constructor->ws, widget_label, 0, widget);
	return (0);
}
