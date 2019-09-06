/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_templates_image.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:48:48 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:48:56 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_surface.h>
#include <libui_widgets_templates.h>

int		libui_widgets_templates_image(t_libui_widget *out,
	const char *path, SDL_Rect rect)
{
	*out = libui_widgets_templates_null();
	if ((out->texture = libui_surface_image_load_32argb(path,
													rect.w, rect.h)) == NULL)
		return (-1);
	out->type = LUI_WT_IMAGE;
	out->rect = rect;
	out->need_redraw = 1;
	return (0);
}
