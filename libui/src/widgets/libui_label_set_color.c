/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_label_set_color.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:43:23 by tfernand          #+#    #+#             */
/*   Updated: 2019/04/03 14:46:40 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_label_set_color(t_libui_widget *widget, SDL_Color color)
{
	t_libui_widget_text	*data;

	if (widget->type == LUI_WT_TEXT)
	{
		data = (t_libui_widget_text *)widget->data;
		data->color = color;
		libui_redraw_label_texture(widget);
	}
}
