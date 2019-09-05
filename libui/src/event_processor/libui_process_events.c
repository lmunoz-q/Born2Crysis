/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_process_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:35 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/27 16:57:18 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui.h>

static inline int	process_events(t_libui_window *win, SDL_Event *event,
	t_libui_env *env, t_libui_pixel_coord cursor)
{
	t_libui_widget			*w;
	t_libui_widgets_surface	*ws;

	if (event->type == SDL_WINDOWEVENT
		&& event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		event->type = SDL_USEREVENT;
		event->user.type = env->discarded_event;
	}
	if (SDL_GetRelativeMouseMode() == SDL_FALSE && (w = NULL) == NULL)
	{
		ws = win->widgets_surface;
		while (ws != NULL && ws->next != NULL)
			ws = ws->next;
		while (ws != NULL)
		{
			w = ws->pixel_bound_widget[cursor.x + cursor.y * ws->surface->w];
			if (!handle_hover_event(event, ws, w))
				break ;
			ws = ws->previous;
		}
		handle_pressed_event(event, win, w);
		handle_keydown_event(event, win);
	}
	return (event->type != SDL_LASTEVENT);
}

/*
** get the mouse state relative to the surface of the window and not the window
** itself
*/

static inline void	get_mouse_state(t_libui_window *win, int *x, int *y)
{
	int		w;
	int		h;

	SDL_GetWindowSize(win->ptr, &w, &h);
	SDL_GetMouseState(x, y);
	*x = (int)((((double)*x) / ((double)w)) * (double)win->surface->w);
	*y = (int)((((double)*y) / ((double)h)) * (double)win->surface->h);
}

int					libui_process_events(SDL_Event *event)
{
	SDL_Window			*ptr;
	t_libui_window		*win;
	t_libui_env			*env;
	t_libui_pixel_coord	cursor;

	env = libui_env();
	if (SDL_PollEvent(event))
	{
		if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN
			|| event->type == SDL_MOUSEBUTTONUP
			|| event->type == SDL_MOUSEWHEEL
			|| event->type == SDL_MOUSEWHEEL_FLIPPED
			|| event->type == SDL_MOUSEWHEEL_NORMAL)
			ptr = SDL_GetMouseFocus();
		else
			ptr = SDL_GetKeyboardFocus();
		if ((win = SDL_GetWindowData(ptr, "t_libui_window")) == NULL)
			return (1);
		get_mouse_state(win, &cursor.x, &cursor.y);
		if (win->widgets_surface != NULL)
			return (process_events(win, event, env, cursor));
		return (1);
	}
	return (0);
}
