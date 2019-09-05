/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_callback_received_keydown.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:11:43 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 16:57:34 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void		libui_callback_received_keydown(t_libui_widget *widget, char *key)
{
	char				*new_text;
	t_libui_inputtext	*data;

	if (!widget || !key || !((t_libui_inputtext *)widget->data))
		return ;
	if (widget->type == LUI_WT_INPUTTEXT)
	{
		data = ((t_libui_inputtext *)widget->data);
		new_text = data->text;
		if (*key == '\b')
		{
			if (data->text_len > 0)
				data->text_len--;
			new_text[data->text_len] = '\0';
		}
		else
		{
			SDL_strlcat(new_text, key, data->text_max_len);
			data->text_len++;
			if (data->text_len > data->text_max_len)
				data->text_len = data->text_max_len;
		}
		libui_label_set_text(widget->shilds, new_text);
	}
}
