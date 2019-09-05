/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_label_get_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 17:50:20 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/26 17:51:14 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

char	*libui_label_get_text(t_libui_widget *widget)
{
	t_libui_widget_text	*data;

	if (widget->type == LUI_WT_TEXT)
	{
		data = (t_libui_widget_text *)widget->data;
		return (data->ptr);
	}
	return (NULL);
}
