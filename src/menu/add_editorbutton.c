/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_editorbutton.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:07:48 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 18:08:02 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

int		add_editorbutton(t_e *e, t_libui_widget *widget_buttoneditor,
	t_libui_widget *widget_labeleditor, TTF_Font *font, t_double_color *theme,
	SDL_bool *running)
{
	SDL_Rect size;

	size.x = 100;
	size.y = e->win->surface->h - 325;
	size.h = 100;
	size.w = e->win->surface->w - 200;
	if (!libui_create_button(widget_buttoneditor, size, 0xffaaaaaa))
		return (-1);
	libui_widgets_add_widget(e->win->widgets_surface, widget_buttoneditor, 0,
		NULL);
	widget_buttoneditor->on_hover.callback = change_color;
	widget_buttoneditor->on_hover.filter = SDL_MOUSEMOTION;
	widget_buttoneditor->on_hover.user_data = theme;
	widget_buttoneditor->on_hover.widget = widget_buttoneditor;
	widget_buttoneditor->on_press.callback = switch_bool;
	widget_buttoneditor->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget_buttoneditor->on_press.user_data = running;
	widget_buttoneditor->on_press.widget = widget_buttoneditor;
	size.x = 10;
	size.y = 10;
	size.h = 80;
	size.w = e->win->surface->w - 200;
	if (!libui_create_label(widget_labeleditor, size, "Editor", font))
		return (-1);
	libui_widgets_add_widget(e->win->widgets_surface,
		widget_labeleditor, 0, widget_buttoneditor);
	return (0);
}
