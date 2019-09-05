/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_events_handles.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:34:35 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/27 16:57:18 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui.h>

inline int			handle_pressed_event(SDL_Event *event, t_libui_window *win,
										t_libui_widget *w)
{
	if (event->type == SDL_MOUSEBUTTONDOWN
		&& event->button.button == SDL_BUTTON_LEFT)
	{
		if (w != NULL)
			win->focused_widget = w;
		if (w != NULL && w->on_press.callback != NULL)
		{
			win->widgets_surface->pressed = w;
			libui_call_back(&w->on_press, event);
		}
		else if (w != NULL && w->on_key_pressed == NULL)
		{
			handle_pressed_event(event, win, w->parent);
		}
		else if (w != NULL && w->on_key_pressed != NULL)
			return (0);
		else
			return (1);
		return (0);
	}
	return (1);
}

static inline void	change_hovered_widget(SDL_Event *event,
							t_libui_widgets_surface *ws, t_libui_widget *new_w)
{
	if (ws->hovered != NULL)
	{
		ws->hovered->is_hover = 0;
		if (ws->hovered->on_hover.callback != NULL)
			libui_call_back(&ws->hovered->on_hover, event);
	}
	ws->hovered = new_w;
}

inline int			handle_hover_event(SDL_Event *event,
								t_libui_widgets_surface *ws, t_libui_widget *w)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		if (w != NULL)
		{
			if (w->is_hover == 0)
			{
				change_hovered_widget(event, ws, w);
				w->is_hover = 1;
				if (w->on_hover.callback != NULL)
					libui_call_back(&w->on_hover, event);
				else
				{
					return (handle_hover_event(event, ws, w->parent));
				}
			}
			return (0);
		}
		else
		{
			change_hovered_widget(event, ws, NULL);
			return (1);
		}
	}
	return (1);
}

inline int			handle_keydown_event(SDL_Event *event,
										t_libui_window *win)
{
	t_libui_widget	*w;

	w = win->focused_widget;
	if (w == NULL)
		return (1);
	if (event->type == SDL_TEXTINPUT)
	{
		if (w->on_key_pressed != NULL)
		{
			w->on_key_pressed(w, event->text.text);
			return (0);
		}
	}
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE)
		{
			if (w->on_key_pressed != NULL)
			{
				w->on_key_pressed(w, "\b");
				return (0);
			}
		}
	}
	return (1);
}
