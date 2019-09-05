/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_progressbar_set_value.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:07:21 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 22:46:07 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	libui_progressbar_set_current_value(t_libui_widget *widget,
	int new_value)
{
	t_libui_widget_progressbar	*data;

	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
	{
		data = (t_libui_widget_progressbar *)widget->data;
	}
	else
		return ;
	data->value_current = new_value;
	if (data->value_current > data->value_max)
		data->value_current = data->value_max;
	else if (data->value_current < data->value_min)
		data->value_current = data->value_min;
	libui_redraw_progressbar_texture(widget);
}

void	libui_progressbar_set_minmax_value(t_libui_widget *widget,
	int new_min_value, int new_max_value)
{
	t_libui_widget_progressbar	*data;

	data = NULL;
	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
	{
		data = (t_libui_widget_progressbar *)widget->data;
	}
	if (data != NULL)
	{
		data->value_min = new_min_value;
		data->value_max = new_max_value;
		if (data->value_max <= data->value_min)
			data->value_max = data->value_min + 1;
		if (data->value_current > data->value_max)
			data->value_current = data->value_max;
		else if (data->value_current < data->value_min)
			data->value_current = data->value_min;
		libui_redraw_progressbar_texture(widget);
	}
}
