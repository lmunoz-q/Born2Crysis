/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quitbutton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:12:08 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 18:12:09 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

int		add_quitbutton(t_e *e, t_libui_widget *widget_buttonquitter,
	t_libui_widget *widget_labelquitter, TTF_Font *font,
	t_double_color *theme, SDL_bool *running)
{
	SDL_Rect		size;

	size.x = 100;
	size.y = e->win->surface->h - 200;
	size.h = 100;
	size.w = e->win->surface->w - 200;
	if (!libui_create_button(widget_buttonquitter, size, 0xffaaaaaa))
		return (-1);
	libui_widgets_add_widget(e->win->widgets_surface, widget_buttonquitter,
		0, NULL);
	widget_buttonquitter->on_hover.callback = change_color;
	widget_buttonquitter->on_hover.filter = SDL_MOUSEMOTION;
	widget_buttonquitter->on_hover.user_data = theme;
	widget_buttonquitter->on_hover.widget = widget_buttonquitter;
	widget_buttonquitter->on_press.callback = switch_bool;
	widget_buttonquitter->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget_buttonquitter->on_press.user_data = running;
	widget_buttonquitter->on_press.widget = widget_buttonquitter;
	size.x = 10;
	size.y = 10;
	size.h = 80;
	size.w = e->win->surface->w - 200;
	if (!libui_create_label(widget_labelquitter, size, "Quitter", font))
		return (-1);
	libui_widgets_add_widget(e->win->widgets_surface, widget_labelquitter, 0,
		widget_buttonquitter);
	return (0);
}
