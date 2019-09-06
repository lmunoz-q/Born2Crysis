/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_main_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfischer <mfischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 12:41:26 by tfernand          #+#    #+#             */
/*   Updated: 2019/09/01 19:59:29 by mfischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "doom_nukem.h"
#include "menu.h"
#include <SDL2/SDL.h>

static void	clear_for_switch_scene(t_libui_widgets_surface *ws, t_e *e)
{
	free(ws->pixel_bound_widget);
	SDL_FreeSurface(ws->surface);
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH,
			LUI_DEFAULT_WINDOW_HEIGHT},
		ws);
	libui_window_update(e->win);
}

static void	init_main_menu(t_e *e, t_menu_content *menu_content,
	t_libui_widgets_surface *ws)
{
	menu_content->theme.second_color = 0xff999999;
	menu_content->theme.first_color = 0xffcccccc;
	libui_widgets_new_widgets_surface(
		(SDL_Rect){0, 0, LUI_DEAULT_WINDOW_WIDTH, LUI_DEFAULT_WINDOW_HEIGHT},
		ws);
	e->win->widgets_surface = ws;
	e->win->refresh_rate = 60;
	menu_content->font = TTF_OpenFont("./libui/resources/Prototype.ttf", 64);
	menu_content->game_running = SDL_FALSE;
	menu_content->editor_running = SDL_FALSE;
	if (menu_content->font)
	{
		add_quitbutton(e, menu_content);
		add_editorbutton(e, menu_content);
		add_playbutton(e, menu_content);
	}
}

static void	main_loop(t_e *e, t_menu_content *menu_content,
	t_libui_widgets_surface *ws)
{
	if (menu_content->game_running == SDL_TRUE)
	{
		clear_for_switch_scene(ws, e);
		init_game_state(e);
		run_game(e);
		menu_content->win_running = SDL_FALSE;
	}
	if (menu_content->editor_running == SDL_TRUE)
	{
		clear_for_switch_scene(ws, e);
		launch_editor_interface(e);
		menu_content->win_running = SDL_FALSE;
	}
}

void		launch_main_menu(t_e *e)
{
	t_libui_widgets_surface		ws;
	SDL_Event					event;
	t_menu_content				menu_content;

	init_main_menu(e, &menu_content, &ws);
	menu_content.win_running = SDL_TRUE;
	while (menu_content.win_running)
	{
		if (libui_process_events(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN
					&& event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				break ;
		}
		if (libui_window_process_fps(e->win))
			libui_window_update(e->win);
		main_loop(e, &menu_content, &ws);
	}
	TTF_CloseFont(menu_content.font);
	libui_widgets_surface_destroy(&ws);
	libui_widget_destroy(&menu_content.widget_buttonplay);
	libui_widget_destroy(&menu_content.widget_buttoneditor);
	libui_widget_destroy(&menu_content.widget_buttonquitter);
}
