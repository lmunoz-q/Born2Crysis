/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_clear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:05:36 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 16:59:25 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>

/*
** clear the video buffer of the window (set all pixels to 0x00000000)
*/

void	libui_window_clear(t_libui_window *win)
{
	SDL_memset(win->surface->pixels, 0xff000000,
		(size_t)win->surface->h * win->surface->pitch);
}

void	libui_window_clear_atomic(t_libui_window *win)
{
	SDL_Surface	*surface;

	SDL_LockMutex(win->mutex);
	surface = win->surface;
	SDL_LockSurface(surface);
	SDL_memset(surface->pixels, 0xff000000, (size_t)surface->h
		* surface->pitch);
	SDL_UnlockSurface(surface);
	SDL_UnlockMutex(win->mutex);
}
