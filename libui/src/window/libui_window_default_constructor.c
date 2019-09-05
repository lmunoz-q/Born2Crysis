/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_default_constructor.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:07:40 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 16:59:34 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>
#include <libui_surface.h>

t_libui_window_constructor	libui_window_default_constructor(void)
{
	return ((t_libui_window_constructor){.rect = {.x = SDL_WINDOWPOS_UNDEFINED,
		.y = SDL_WINDOWPOS_UNDEFINED, .w = LUI_DEAULT_WINDOW_WIDTH,
		.h = LUI_DEFAULT_WINDOW_HEIGHT}, .name = LUI_DEFAULT_WINDOW_NAME,
		.winow_flags = SDL_WINDOW_SHOWN,
		.renderer_flags = SDL_RENDERER_ACCELERATED,
		.refresh_rate = LUI_DEFAULT_REFRESH_RATE,
		.surface_flags = LIBUI_SURFACE_FLAGS, .depth = LIBUI_SURFACE_DEPTH,
		.red_mask = LIBUI_SURFACE_RED_MASK,
		.green_mask = LIBUI_SURFACE_GREEN_MASK,
		.blue_mask = LIBUI_SURFACE_BLUE_MASK,
		.alpha_mask = LIBUI_SURFACE_ALPHA_MASK});
}
