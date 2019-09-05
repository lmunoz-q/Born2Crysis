/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_progressbar_set_colors.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:31:08 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 22:27:34 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_progressbar_set_colors(t_libui_widget *widget,
	int new_backcolor, int new_frontcolor)
{
	t_libui_widget_progressbar	*data;

	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
	{
		data = (t_libui_widget_progressbar *)widget->data;
		data->back_color = new_backcolor;
		data->front_color = new_frontcolor;
		libui_redraw_progressbar_texture(widget);
	}
}
