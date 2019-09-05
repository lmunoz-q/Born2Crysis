/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_delete.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:59:38 by tfernand          #+#    #+#             */
/*   Updated: 2019/08/22 16:59:58 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>

void	libui_window_delete(t_libui_window *win)
{
	SDL_FreeSurface(win->surface);
	SDL_DestroyMutex(win->mutex);
	SDL_DestroyWindow(win->ptr);
	SDL_DestroyRenderer(win->renderer);
	free(win);
}
