/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_window_title.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:07:03 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 17:00:10 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_window.h>
#include <stdarg.h>

/*
** replace the current title by a new type using a printf-like format (limited
** to 4096 characters)
*/

int		libui_window_title(t_libui_window *win, const char *format, ...)
{
	char	buffer[4096];
	va_list	vl;
	int		ret;

	va_start(vl, format);
	ret = vsnprintf(buffer, 4096, format, vl);
	va_end(vl);
	SDL_LockMutex(win->mutex);
	SDL_SetWindowTitle(win->ptr, buffer);
	SDL_UnlockMutex(win->mutex);
	return (ret);
}
