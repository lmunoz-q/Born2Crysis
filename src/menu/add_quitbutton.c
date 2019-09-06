/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quitbutton.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 18:12:08 by lmunoz-q          #+#    #+#             */
/*   Updated: 2019/08/31 18:51:25 by tfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

int		add_quitbutton(t_e *e, t_menu_content *menu_content)
{
	t_libui_textbutton_constructor	cons;

	libui_init_textbutton_constructor(&cons);
	cons.rect.x = 100;
	cons.rect.y = e->win->surface->h - 200;
	cons.rect.h = 100;
	cons.rect.w = e->win->surface->w - 200;
	cons.font = menu_content->font;
	cons.text = "Quitter";
	cons.theme = &menu_content->theme;
	cons.ws = e->win->widgets_surface;
	cons.label_rect.x = 10;
	cons.label_rect.y = 10;
	cons.label_rect.h = 100;
	cons.label_rect.w = e->win->surface->w - 200;
	if (libui_create_textbutton(&menu_content->widget_buttonquitter, &cons))
		return (-1);
	libui_callback_setpressed(&(menu_content->widget_buttonquitter),
		libui_callback_toggle_bool, SDL_MOUSEBUTTONDOWN,
		&(menu_content->win_running));
	return (0);
}
