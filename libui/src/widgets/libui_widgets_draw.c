/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_widgets_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:10:15 by hmartzol          #+#    #+#             */
/*   Updated: 2019/08/22 17:40:23 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libui_env.h>
#include <libui_window.h>
#include <libui_widgets.h>
#include <libui_callback.h>

static void			i_rect_parent(SDL_Surface *surface, t_libui_widget *w,
	SDL_Rect widget_area)
{
	SDL_Event		event;
	SDL_Rect		widget_pos;
	SDL_Rect		t;

	widget_pos = (SDL_Rect){widget_area.x - w->rect.x,
		widget_area.y - w->rect.y, widget_area.w, widget_area.h};
	if (w->is_hiden || w->translucid == 1)
	{
		t = w->is_hiden ? widget_pos : widget_area;
		if (w->parent != NULL)
			i_rect_parent(surface, w->parent, t);
		else
			SDL_FillRect(surface, &t, 0x00000000);
		if (w->is_hiden)
			return ;
	}
	if (w->on_redraw.callback != NULL)
	{
		event.type = SDL_USEREVENT;
		event.user.type = libui_env()->widget_redraw_event;
		libui_call_back(&w->on_redraw, &event);
	}
	if (w->texture != NULL)
		SDL_BlitSurface(w->texture, &widget_pos, surface, &widget_area);
}

static inline void	i_rec_0(SDL_Surface *surface, t_libui_widget *w,
	SDL_Rect widget_pos)
{
	t_libui_widget	*tmp;

	if (w->is_hiden)
	{
		if (w->parent != NULL)
			i_rect_parent(surface, w->parent, widget_pos);
		else
			SDL_FillRect(surface, &widget_pos, 0x00000000);
	}
	if (w->shilds != NULL)
	{
		tmp = w->shilds;
		while (tmp)
		{
			tmp->need_redraw |= 1;
			tmp = tmp->next;
		}
		libui_widgets_draw_rec(surface, w->shilds);
	}
	if (w->next != NULL)
		libui_widgets_draw_rec(surface, w->next);
}

void				libui_widgets_draw_rec(SDL_Surface *surface,
	t_libui_widget *w)
{
	SDL_Event		event;
	SDL_Rect		widget_pos;
	SDL_Rect		src_widget;

	src_widget = w->rect;
	widget_pos = (SDL_Rect){w->rect.x, w->rect.y, src_widget.w, src_widget.h};
	if (!w->is_hiden && w->need_redraw)
	{
		if (w->translucid == 1 && w->parent != NULL)
			i_rect_parent(surface, w->parent, widget_pos);
		src_widget.x = 0;
		src_widget.y = 0;
		if (w->on_redraw.callback != NULL)
		{
			event.type = SDL_USEREVENT;
			event.user.type = libui_env()->widget_redraw_event;
			libui_call_back(&w->on_redraw, &event);
		}
		if (w->texture != NULL)
			SDL_BlitSurface(w->texture, &src_widget, surface, &widget_pos);
		w->need_redraw ^= 1;
	}
	i_rec_0(surface, w, widget_pos);
}

int					libui_widgets_draw(t_libui_widgets_surface *ws)
{
	t_libui_widget	*w;

	while (ws != NULL)
	{
		w = ws->widgets;
		while (w != NULL)
		{
			libui_widgets_draw_rec(ws->surface, w);
			w = w->next;
		}
		ws = ws->next;
	}
	return (0);
}
