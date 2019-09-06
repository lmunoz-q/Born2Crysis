/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:25:59 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/27 16:44:05 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>

static inline t_libui_window	*i_finalize(t_libui_window *out,
											t_libui_window *parent)
{
	(void)SDL_SetWindowData(out->ptr, "t_libui_window", out);
	if (parent != NULL)
		parent->shild = out;
	out->mutex = SDL_CreateMutex();
	if (out->mutex == NULL)
	{
		SDL_DestroyRenderer(out->renderer);
		SDL_DestroyWindow(out->ptr);
		SDL_free(out);
		return (NULL);
	}
	return (out);
}

t_libui_window					*libui_window_create(
								const t_libui_window_constructor c,
								t_libui_window *parent,
								t_libui_window *prev,
								t_libui_window *next)
{
	t_libui_window	*out;

	if ((out = SDL_malloc(sizeof(t_libui_window))) == NULL)
		return (NULL);
	*out = (t_libui_window){.constructor = c, .parent = parent, .shild = NULL,
		.prev = prev, .next = next, .frame = 0, .fps = 0,
		.ptr = SDL_CreateWindow(c.name, c.rect.x, c.rect.y, c.rect.w, c.rect.h,
		c.winow_flags), .renderer = NULL, .surface = NULL,
		.widgets_surface = NULL, .refresh_rate = c.refresh_rate,
		.last_tick = 0};
	out->focused_widget = NULL;
	if (out->ptr == NULL || (out->renderer = SDL_CreateRenderer(out->ptr, -1,
		c.renderer_flags)) == NULL
		|| (out->surface = SDL_CreateRGBSurface(c.surface_flags, c.rect.w,
		c.rect.h, c.depth, c.red_mask, c.green_mask, c.blue_mask,
		c.alpha_mask)) == NULL)
	{
		if (out->renderer != NULL)
			SDL_DestroyRenderer(out->renderer);
		SDL_DestroyWindow(out->ptr);
		SDL_free(out);
		return (NULL);
	}
	return (i_finalize(out, parent));
}
