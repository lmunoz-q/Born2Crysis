/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_refresh.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:47:43 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 17:00:07 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>

/*
** atomic by default
*/

int	libui_window_refresh(t_libui_window *win)
{
	static SDL_Texture	*tmp = NULL;

	SDL_RenderClear(win->renderer);
	SDL_LockSurface(win->surface);
	if (!tmp)
		if (!(tmp = SDL_CreateTextureFromSurface(win->renderer, win->surface)))
			return (-1);
	SDL_UpdateTexture(tmp, NULL, win->surface->pixels, win->surface->pitch);
	SDL_UnlockSurface(win->surface);
	SDL_RenderCopy(win->renderer, tmp, NULL, NULL);
	SDL_RenderPresent(win->renderer);
	win->last_tick = SDL_GetTicks();
	++win->frame;
	return (0);
}
