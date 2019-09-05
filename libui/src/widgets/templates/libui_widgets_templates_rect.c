/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_templates_rect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:49:40 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:49:41 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets_templates.h>

int	libui_widgets_templates_rect(t_libui_widget *out, SDL_Rect rect)
{
	*out = libui_widgets_templates_null();
	out->type = LUI_WT_ACTIVABLE;
	out->rect = rect;
	return (0);
}
