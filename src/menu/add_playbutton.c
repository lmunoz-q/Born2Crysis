/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_playbutton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmunoz-q <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:13:02 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 18:13:03 by lmunoz-q         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

int		add_playbutton(t_e *e, t_libui_widget *widget_buttonplay,
	t_libui_widget *widget_labelplay, TTF_Font *font, t_double_color *theme,
	SDL_bool *running)
{
	SDL_Rect size;

	size.x = 100;
	size.y = e->win->surface->h - 450;
	size.h = 100;
	size.w = e->win->surface->w - 200;
	if (!libui_create_button(widget_buttonplay, size, 0xffaaaaaa))
	{
		printf("Unable to create the button\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface,
		widget_buttonplay, 0, NULL);
	widget_buttonplay->on_hover.callback = change_color;
	widget_buttonplay->on_hover.filter = SDL_MOUSEMOTION;
	widget_buttonplay->on_hover.user_data = theme;
	widget_buttonplay->on_hover.widget = widget_buttonplay;
	widget_buttonplay->on_press.callback = switch_bool;
	widget_buttonplay->on_press.filter = SDL_MOUSEBUTTONDOWN;
	widget_buttonplay->on_press.user_data = running;
	widget_buttonplay->on_press.widget = widget_buttonplay;
	size.x = 10;
	size.y = 10;
	size.h = 80;
	size.w = e->win->surface->w - 200;
	if (!libui_create_label(widget_labelplay, size, "Jouer solo", font))
	{
		printf("Unable to create the label\n");
		return (-1);
	}
	libui_widgets_add_widget(e->win->widgets_surface,
		widget_labelplay, 0, widget_buttonplay);
	return (0);
}
