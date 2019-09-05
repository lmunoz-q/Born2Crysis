/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_menu_add_option.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:35:05 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:53:55 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

t_libui_widget			*add_option_button(t_libui_widget *menu,
		char *new_option, TTF_Font *font)
{
	t_libui_widget						*button;
	t_libui_widget_menu					*menu_data;
	t_libui_textbutton_constructor		construc;
	static const t_libui_double_color	theme = (t_libui_double_color)

	{.second_color = 0xff999999, .first_color = 0xffcccccc};
	menu_data = (t_libui_widget_menu *)menu->data;
	if (!(button = (t_libui_widget *)malloc(sizeof(t_libui_widget))))
		return (NULL);
	construc = (t_libui_textbutton_constructor){menu_data->selecteur.ws,
		&menu_data->selecteur, {0, menu_data->current_height,
		menu_data->option_height, menu_data->selecteur.rect.w}, {0, 0,
		construc.rect.h, construc.rect.w}, new_option, font, &theme};
	menu_data->current_height = menu_data->current_height
		+ menu_data->option_height;
	menu_data->selecteur.rect.h = menu_data->current_height + 5;
	if (libui_create_textbutton(button, &construc))
	{
		free(button);
		return (NULL);
	}
	libui_widget_set_visibility(button, 0, 1, 0);
	return (button);
}

t_libui_callback_holder	*libui_menu_add_option(t_libui_widget *widget,
	char *text, TTF_Font *font)
{
	t_libui_callback_holder	*callback;
	t_libui_widget			*option;

	callback = NULL;
	if (widget->type == LUI_WT_MENU)
	{
		option = add_option_button(widget, text, font);
		callback = &option->on_press;
	}
	return (callback);
}
