/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_templates_null.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:49:00 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/27 15:28:04 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_widgets_templates.h>

t_libui_widget	libui_widgets_templates_null(void)
{
	const t_libui_widget	widget = {.next = NULL, .translucid = 0,

	.is_hiden = 0, .shilds = NULL, .has_focus = 0, .parent = NULL, .ws = NULL,
	.type = LUI_WT_UNDEFINED, .data = NULL, .on_press = {.callback = NULL,
	.user_data = NULL, .widget = NULL, .filter = SDL_FIRSTEVENT}, .is_hover = 0,
	.need_redraw = 0, .on_release = {.callback = NULL, .user_data = NULL,
	.widget = NULL, .filter = SDL_FIRSTEVENT}, .on_hover = {.callback = NULL,
	.user_data = NULL, .widget = NULL, .filter = SDL_FIRSTEVENT},
	.is_pressed = 0, .on_redraw = {.callback = NULL, .user_data = NULL,
	.widget = NULL, .filter = SDL_FIRSTEVENT}, .on_key_pressed = NULL,
	.rect = {0, 0, 0, 0}, .relative_pos = {0, 0}, .texture = NULL,
	.on_visibility_change = {.callback = NULL, .user_data = NULL,
	.widget = NULL, .filter = SDL_FIRSTEVENT}};
	return (widget);
}
