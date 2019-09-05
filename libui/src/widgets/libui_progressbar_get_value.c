/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_progressbar_get_value.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:53:59 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/29 22:27:26 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int	libui_progressbar_get_current_value(t_libui_widget *widget)
{
	t_libui_widget_progressbar	*data;

	data = NULL;
	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
	{
		data = (t_libui_widget_progressbar *)widget->data;
	}
	if (data != NULL)
	{
		return (data->value_current);
	}
	return (0);
}

int	libui_progressbar_get_max_value(t_libui_widget *widget)
{
	t_libui_widget_progressbar	*data;

	data = NULL;
	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
	{
		data = (t_libui_widget_progressbar *)widget->data;
	}
	if (data != NULL)
	{
		return (data->value_max);
	}
	return (0);
}

int	libui_progressbar_get_min_value(t_libui_widget *widget)
{
	t_libui_widget_progressbar	*data;

	data = NULL;
	if (widget->type == LUI_WT_PROGRESSBAR || widget->type == LUI_WT_SLIDER)
	{
		data = (t_libui_widget_progressbar *)widget->data;
	}
	if (data != NULL)
	{
		return (data->value_min);
	}
	return (0);
}
