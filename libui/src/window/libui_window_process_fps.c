/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_process_fps.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:02 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 17:00:04 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>

/*
** return values:
** 0: no need to refresh the window
** 1: the window should be refreshed
*/

int	libui_window_process_fps(t_libui_window *win)
{
	int	current_tick;
	int	update;
	int	div;

	update = 0;
	current_tick = SDL_GetTicks();
	SDL_LockMutex(win->mutex);
	if (win->last_tick / 1000 < current_tick / 1000)
	{
		win->fps = win->frame;
		win->frame = 0;
	}
	div = (int)(1000. / (double)win->refresh_rate);
	if (win->last_tick / div < current_tick / div)
		update = 1;
	win->last_tick = current_tick;
	SDL_UnlockMutex(win->mutex);
	return (update);
}
