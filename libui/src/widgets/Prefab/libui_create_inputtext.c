/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_create_inputtext.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:53:11 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 16:27:20 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

static void	str_clean(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		str[i] = '\0';
		i++;
	}
}

int			libui_create_inputtext(t_libui_widget *widget,
						t_libui_inputtext_constructor *c)
{
	t_libui_widget		*label;
	t_libui_inputtext	*data;

	if (!libui_create_container(widget, c->rect, c->back_color)
		|| (label = (t_libui_widget*)malloc(sizeof(t_libui_widget))) == NULL)
		return (0);
	str_clean(c->text, c->text_max_len);
	if (!libui_create_label(label, c->label_rect, c->text, c->font)
	|| (data = (t_libui_inputtext*)malloc(sizeof(t_libui_inputtext))) == NULL)
	{
		free(label);
		return (0);
	}
	data->text = c->text;
	data->text_max_len = c->text_max_len;
	data->text_len = 0;
	widget->type = LUI_WT_INPUTTEXT;
	widget->data = data;
	widget->on_key_pressed = libui_callback_received_keydown;
	libui_label_set_color(label, c->font_color);
	libui_widgets_add_widget(c->ws, widget, 0, c->parent);
	libui_widgets_add_widget(c->ws, label, 0, widget);
	return (1);
}
