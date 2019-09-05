/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_resize_window_surface.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:58:46 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:59:18 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>

/*
** this does not notify the widgets that the surface has been resized
** the widgets need to be rebuild
*/

static inline int	i_fail(SDL_Surface *ns)
{
	if (ns != NULL)
		SDL_FreeSurface(ns);
	return (-1);
}

int					libui_resize_window_surface(t_libui_window *win,
	int w, int h)
{
	SDL_Surface	*new_surface;

	new_surface = SDL_CreateRGBSurface(win->constructor.surface_flags, w, h,
		win->constructor.depth, win->constructor.red_mask,
		win->constructor.green_mask, win->constructor.blue_mask,
		win->constructor.alpha_mask);
	if (new_surface == NULL)
		return (-1);
	if (SDL_BlitScaled(win->surface, NULL, new_surface, NULL) < 0)
		return (i_fail(new_surface));
	SDL_LockMutex(win->mutex);
	SDL_FreeSurface(win->surface);
	win->surface = new_surface;
	SDL_UnlockMutex(win->mutex);
	return (0);
}
