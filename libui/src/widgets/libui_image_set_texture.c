/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_image_set_texture.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:28:19 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:50:46 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

int		libui_image_set_texture(t_libui_widget *widget, char *path)
{
	if (widget->type == LUI_WT_IMAGE)
	{
		if ((widget->texture = libui_surface_image_load_32argb(path,
			widget->rect.w, widget->rect.h)) == NULL)
			return (0);
		widget->need_redraw = 1;
	}
	return (1);
}
