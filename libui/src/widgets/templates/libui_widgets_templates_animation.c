/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_templates_animation.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:48:39 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:48:46 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets_templates.h>

int				libui_widgets_templates_animation(t_libui_widget *out,
													SDL_Rect rect,
													t_libui_callback *cb,
													void *user_data)
{
	*out = libui_widgets_templates_null();
	out->rect = rect;
	out->on_redraw = (t_libui_callback_holder){.callback = cb,
		.user_data = user_data, .filter = SDL_FIRSTEVENT, .widget = out};
	out->type = LUI_WT_ANIMATION;
	out->need_redraw = 2;
	return (0);
}
