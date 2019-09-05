/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_label_set_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:15:46 by tfernand          #+#    #+#             */
/*   Updated: 2019/04/03 14:46:36 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_label_set_text(t_libui_widget *widget, char *text)
{
	char				*old;
	t_libui_widget_text	*data;

	if (widget->type == LUI_WT_TEXT)
	{
		data = (t_libui_widget_text *)widget->data;
		old = data->ptr;
		data->ptr = SDL_strdup(text);
		free(old);
		libui_redraw_label_texture(widget);
	}
}
